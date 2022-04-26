#include "Level.h"
#include "Unit.h"
Level* Level::m_activeLevel;
void Level::init()
{
	m_activeLevel = new Level();
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
