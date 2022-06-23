#include "Unit.h"
#include "LevelInstance.h"
#include "render/RManager.h"
#include "render/RInstance.h"

LevelInstance::LevelInstance(vec3 offset)
	:m_offset{ offset }
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

void LevelInstance::attachObject(LocatedObject* object)
{
	m_objects.pushFront(object);
}

void LevelInstance::attachUnit(Unit* unit)
{
	m_units.pushFront(unit);
	unit->m_levelInstance = this;
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
