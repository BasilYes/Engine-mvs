#pragma once
#include "other/LinkedList.h"
class LocatedObject;
class Unit;
class Level
{
public:

	static void init(Level* lvl);
	static Level* getActiveLevel() { return m_activeLevel; }
	void tick();

	void attachObject(LocatedObject* object);
	void attachUnit(Unit* unit);
	Level();
	~Level();
private:
	static Level* m_activeLevel;
	LincedList<LocatedObject> m_objects;
	LincedList<Unit> m_units;
};