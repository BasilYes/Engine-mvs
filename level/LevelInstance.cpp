#include "Unit.h"
#include "LevelInstance.h"
#include "render/RManager.h"
#include "render/RInstance.h"
#include "game/render/LandscapeFragment.h"

LevelInstance::LevelInstance(vec3 offset, vec2 size)
	:m_offset{ offset }
	,m_size{size}
	,m_ownedRInstance{RManager::getRManager()->addRInstance(this)}
{
}

LevelInstance::~LevelInstance()
{
	LincedListItem<Unit>* unit = m_units.getFirst();
	while (unit)
	{
		delete unit->getContent();
		unit = unit->getNext();
	}
	LincedListItem<LocatedObject>* object = m_objects.getFirst();
	while (object)
	{ 
		delete object->getContent();
		object = object->getNext();
	}
	delete m_ownedRInstance;
}

bool LevelInstance::updateUnitLocation(Unit* unit)
{
	if (unit->getLocation().data[0] < 0.0f)
	{
		unit->remove();
		m_lowerX->attachUnit(unit);
		unit->setUnitLocation(unit->getLocation() + vec3{m_size.data[0], 0.0f, 0.0f});
		return true;
	}
	else if (unit->getLocation().data[0] > m_size.data[0])
	{
		unit->remove();
		m_higherX->attachUnit(unit);
		unit->setUnitLocation(unit->getLocation() - vec3{ m_size.data[0], 0.0f, 0.0f });
		return true;
	}
	else if (unit->getLocation().data[1] < 0.0f)
	{
		unit->remove();
		m_lowerY->attachUnit(unit);
		unit->setUnitLocation(unit->getLocation() + vec3{ 0.0f, m_size.data[1], 0.0f });
		return true;
	}
	else if (unit->getLocation().data[1] > m_size.data[1])
	{
		unit->remove();
		m_higherY->attachUnit(unit);
		unit->setUnitLocation(unit->getLocation() - vec3{ 0.0f, m_size.data[1], 0.0f });
		return true;
	}
	return false;
}

void LevelInstance::attachObject(LocatedObject* object)
{
	m_objects.pushFront(object);
}

void LevelInstance::attachUnit(Unit* unit)
{
	m_units.pushFront(unit);
	unit->m_selfRef = m_units.getFirst();
	unit->attach(this);
}

void LevelInstance::attachRObject(RObject* obj)
{
	m_ownedRInstance->addRObject(obj);
}

void LevelInstance::tick()
{
	LincedListItem<Unit>* unit = m_units.getFirst();
	while (unit)
	{
		unit->getContent()->tick();
		unit = unit->getNext();
	}
}

void LevelInstance::updateCoreInstanse()
{
	updateUp(this);
	updateDown(this);
	updateLeft(this);
	updateRight(this);
}

constexpr float LOD = 450.0f;

void LevelInstance::updateUp(LevelInstance* core)
{
	vec3 offset{ m_offset.data[0], m_offset.data[1] + m_size.data[1], m_offset.data[2]};
	if (m_higherY)
	{
		if ((offset-core->m_offset).len() < LOD)
		{
			m_higherY->updateInstanse();
			m_higherY->updateUp(core);
		}
		else
		{
			m_higherY->updateUp(core);
			if (m_higherY->m_higherX)
				m_higherY->m_higherX->m_lowerX = nullptr;
			if (m_higherY->m_lowerX)
				m_higherY->m_lowerX->m_higherX = nullptr;
			delete m_higherY;
			m_higherY = nullptr;
		}
	}
	else
	{
		if ((offset - core->m_offset).len() < LOD)
		{
			m_higherY = createLevelInstance( offset, m_size );
			m_higherY->m_lowerY = this;
			m_higherY->updateInstanse();
			if (m_lowerX)
			{
				if (m_lowerX->m_higherY)
				{
					m_higherY->m_lowerX = m_lowerX->m_higherY;
					m_lowerX->m_higherY->m_higherX = m_higherY;
				}
			}
			if (m_higherX)
			{
				if (m_higherX->m_higherY)
				{
					m_higherY->m_higherX = m_higherX->m_higherY;
					m_higherX->m_higherY->m_lowerX = m_higherY;
				}
			}
			m_higherY->updateUp(core);
		}
	}
}

void LevelInstance::updateDown(LevelInstance* core)
{
	vec3 offset{ m_offset.data[0], m_offset.data[1] - m_size.data[1], m_offset.data[2] };
	if (m_lowerY)
	{
		if ((offset - core->m_offset).len() < LOD)
		{
			m_lowerY->updateInstanse();
			m_lowerY->updateDown(core);
		}
		else
		{
			m_lowerY->updateDown(core);
			if (m_lowerY->m_higherX)
				m_lowerY->m_higherX->m_lowerX = nullptr;
			if (m_lowerY->m_lowerX)
				m_lowerY->m_lowerX->m_higherX = nullptr;
			delete m_lowerY;
			m_lowerY = nullptr;
		}
	}
	else
	{
		if ((offset - core->m_offset).len() < LOD)
		{
			m_lowerY = createLevelInstance(offset, m_size);
			m_lowerY->m_higherY = this;
			m_lowerY->updateInstanse();
			if (m_lowerX)
			{
				if (m_lowerX->m_lowerY)
				{
					m_lowerY->m_lowerX = m_lowerX->m_lowerY;
					m_lowerX->m_lowerY->m_higherX = m_lowerY;
				}
			}
			if (m_higherX)
			{
				if (m_higherX->m_lowerY)
				{
					m_lowerY->m_higherX = m_higherX->m_lowerY;
					m_higherX->m_lowerY->m_lowerX = m_lowerY;
				}
			}
			m_lowerY->updateDown(core);
		}
	}
}

void LevelInstance::updateRight(LevelInstance* core)
{
	vec3 offset{ m_offset.data[0] + m_size.data[0], m_offset.data[1], m_offset.data[2] };
	if (m_higherX)
	{
		if ((offset - core->m_offset).len() < LOD)
		{
			m_higherX->updateInstanse();
			m_higherX->updateUp(core);
			m_higherX->updateDown(core);
			m_higherX->updateRight(core);
		}
		else
		{
			m_higherX->updateUp(core);
			m_higherX->updateDown(core);
				
			delete m_higherX;
			m_higherX = nullptr;
		}
	}
	else
	{
		if ((offset - core->m_offset).len() < LOD)
		{
			m_higherX = createLevelInstance(offset, m_size);
			m_higherX->m_lowerX = this;
			m_higherX->updateInstanse();
			m_higherX->updateUp(core);
			m_higherX->updateDown(core);
			m_higherX->updateRight(core);
		}
	}
}

void LevelInstance::updateLeft(LevelInstance* core)
{
	vec3 offset{ m_offset.data[0] - m_size.data[0], m_offset.data[1], m_offset.data[2] };
	if (m_lowerX)
	{
		if ((offset - core->m_offset).len() < LOD)
		{
			m_lowerX->updateInstanse();
			m_lowerX->updateUp(core);
			m_lowerX->updateDown(core);
			m_lowerX->updateLeft(core);
		}
		else
		{
			m_lowerX->updateUp(core);
			m_lowerX->updateDown(core);

			delete m_lowerX;
			m_lowerX = nullptr;
		}
	}
	else
	{
		if ((offset - core->m_offset).len() < LOD)
		{
			m_lowerX = createLevelInstance(offset, m_size);
			m_lowerX->m_higherX = this;
			m_lowerX->updateInstanse();
			m_lowerX->updateUp(core);
			m_lowerX->updateDown(core);
			m_lowerX->updateLeft(core);
		}
	}
}

void LevelInstance::updateInstanse()
{

}
