#include "LevelInstance.h"
#include "Unit.h"

LevelInstance::LevelInstance(vec3 offset)
	:m_offset{ offset }
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

void LevelInstance::tick()
{
	LincedListItem<Unit>* unit = m_units.getFirst();
	while (unit)
	{
		unit->getContent()->tick();
		unit = unit->getNext();
	}
}
