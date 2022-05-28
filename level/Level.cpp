#include "Level.h"
#include "Unit.h"

Level* Level::m_activeLevel;
void Level::init(Level* lvl)
{
	ASSERT(!m_activeLevel, "Can't Lvl reinit");
	m_activeLevel = lvl;
}

void Level::tick()
{
	LincedListItem<Unit>* unit = m_units.getFirst();
	while (unit)
	{
		unit->getContent()->tick();
		unit = unit->getNext();
	}
}

void Level::attachObject(LocatedObject* object)
{
	m_objects.pushFront(object);
}

void Level::attachUnit(Unit* unit)
{
	m_units.pushFront(unit);
	unit->m_Level = this;
}

Level::Level()
{
}

Level::~Level()
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