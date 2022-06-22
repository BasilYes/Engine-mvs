#pragma once
#include "other/LinkedList.h"
class LocatedObject;
class Unit;
class LevelInstance
{
public:
	LevelInstance(vec3 offset);
	virtual ~LevelInstance();
	void attachObject(LocatedObject* object);
	void attachUnit(Unit* unit);
	void tick();
private:
	vec3 m_offset;
	LevelInstance* m_higherX = nullptr;
	LevelInstance* m_lowerX = nullptr;
	LevelInstance* m_higherY = nullptr;
	LevelInstance* m_lowerY = nullptr;
	LincedList<LocatedObject> m_objects;
	LincedList<Unit> m_units;
};

