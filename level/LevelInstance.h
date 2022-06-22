#pragma once
#include "other/LinkedList.h"
class LocatedObject;
class Unit;
class LevelInstance
{
public:
	void attachObject(LocatedObject* object);
	void attachUnit(Unit* unit);
	void tick();
private:
	float m_offsetX;
	float m_offsetY;
	LevelInstance* m_higherX;
	LevelInstance* m_lowerX;
	LevelInstance* m_higherY;
	LevelInstance* m_lowerY;
	LincedList<LocatedObject> m_objects;
	LincedList<Unit> m_units;
};

