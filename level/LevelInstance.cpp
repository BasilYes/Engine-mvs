#include "LevelInstance.h"
#include "Unit.h"

void LevelInstance::attachObject(LocatedObject* object)
{
	m_objects.pushFront(object);
}

void LevelInstance::attachUnit(Unit* unit)
{
	m_units.pushFront(unit);
	//unit->m_Level = this;
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
