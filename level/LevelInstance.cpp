#include "Unit.h"
#include "LevelInstance.h"
#include "render/RManager.h"
#include "render/RInstance.h"
#include "Level.h"

LevelInstance::LevelInstance(vec3 offset, vec2 size, uvec2 position, Level* owningLevel)
	:m_offset{ offset }
	,m_size{size}
	,m_position{position}
	,m_owningLevel{owningLevel}
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

		int newX = m_position.data[0] - 1;
		if (newX < 0)
			newX += m_owningLevel->m_size.data[0];
		m_owningLevel->m_instances[newX][m_position.data[1]]->attachUnit(unit);

		unit->setUnitLocation(unit->getLocation() + vec3{m_size.data[0], 0.0f, 0.0f});
		return true;
	}
	else if (unit->getLocation().data[0] > m_size.data[0])
	{
		unit->remove();
		int newX = m_position.data[0] + 1;
		newX %= m_owningLevel->m_size.data[0];
		m_owningLevel->m_instances[newX][m_position.data[1]]->attachUnit(unit);

		unit->setUnitLocation(unit->getLocation() - vec3{ m_size.data[0], 0.0f, 0.0f });
		return true;
	}
	else if (unit->getLocation().data[1] < 0.0f)
	{
		unit->remove();

		int newY = m_position.data[1] - 1;
		if (newY < 0)
			newY += m_owningLevel->m_size.data[1];
		m_owningLevel->m_instances[m_position.data[0]][newY]->attachUnit(unit);

		unit->setUnitLocation(unit->getLocation() + vec3{ 0.0f, m_size.data[1], 0.0f });
		return true;
	}
	else if (unit->getLocation().data[1] > m_size.data[1])
	{
		unit->remove();

		int newY = m_position.data[1] + 1;
		newY %= m_owningLevel->m_size.data[1];
		m_owningLevel->m_instances[m_position.data[0]][newY]->attachUnit(unit);

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

void LevelInstance::updateInstanse()
{

}
