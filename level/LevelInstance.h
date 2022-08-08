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
	virtual ~LevelInstance();

	vec3 getOffset() { return m_offset; }
	uvec2 getPosition() { return m_position; }
	Level* getOwningLevel() { return m_owningLevel; }

	void tick();

	bool updateUnitLocation(Unit* unit);

	void attachObject(LocatedObject* object);
	void attachUnit(Unit* unit);
	void attachRObject(RObject* obj);

protected:
	LevelInstance(vec3 offset, vec2 size, uvec2 position, Level* owningLevel);
	void updateInstanse();

private:
	vec3 m_offset;
	vec2 m_size;
	uvec2 m_position;
	RInstance* m_ownedRInstance;
	Level* m_owningLevel;
	LincedList<LocatedObject> m_objects;
	LincedList<Unit> m_units;
	friend Level;
};

