#pragma once
#include "other/LinkedList.h"
#include "other/math/vector.h"
class LocatedObject;
class Unit;
class RInstance;
class RObject;
class Level;
class LevelInstance
{
public:
	LevelInstance(vec3 offset);
	virtual ~LevelInstance();
	vec3 getOffset() { return m_offset; }
	void attachObject(LocatedObject* object);
	void attachUnit(Unit* unit);
	void attachRObject(RObject* obj);
	void tick();
private:
	vec3 m_offset;
	RInstance* m_ownedRInstance;
	LevelInstance* m_higherX = nullptr;
	LevelInstance* m_lowerX = nullptr;
	LevelInstance* m_higherY = nullptr;
	LevelInstance* m_lowerY = nullptr;
	LincedList<LocatedObject> m_objects;
	LincedList<Unit> m_units;
	friend Level;
};

