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
	LevelInstance(vec3 offset, vec2 size);
	virtual ~LevelInstance();
	virtual LevelInstance* createLevelInstance(vec3 offset, vec2 size) = 0;
	vec3 getOffset() { return m_offset; }
	bool updateUnitLocation(Unit* unit);
	void attachObject(LocatedObject* object);
	void attachUnit(Unit* unit);
	void attachRObject(RObject* obj);
	void tick();
private:
	void updateCoreInstanse();
	void updateInstanse();
	void updateUp(LevelInstance* core);
	void updateDown(LevelInstance* core);
	void updateRight(LevelInstance* core);
	void updateLeft(LevelInstance* core);
	vec3 m_offset;
	vec2 m_size;
	RInstance* m_ownedRInstance;
	LevelInstance* m_higherX = nullptr;
	LevelInstance* m_lowerX = nullptr;
	LevelInstance* m_higherY = nullptr;
	LevelInstance* m_lowerY = nullptr;
	LincedList<LocatedObject> m_objects;
	LincedList<Unit> m_units;
	friend Level;
};

