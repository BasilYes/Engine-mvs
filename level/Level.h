#pragma once
#include "other/LinkedList.h"
#include "other/math/vector.h"
class LocatedObject;
class Unit;
class LevelInstance;
class Level
{
public:
	Level(uvec2 size, vec2 instancesSize, float LOD);
	virtual ~Level();

	static void init(Level* lvl);
	static Level* getActiveLevel() { return m_activeLevel; }
	LevelInstance* getCoreInstance() { return m_instances[m_coreInstance.data[0]][m_coreInstance.data[1]]; }
	vec2 getInstancesSize() { return m_instancesSize; }

	virtual void load();
	virtual LevelInstance* createLevelInstance(vec3 offset, vec2 size, uvec2 position) = 0;
	void updateCoreInstanse(uvec2 position);
	void tick();

private:
	static Level* m_activeLevel;

	uvec2 m_size;
	uvec2 m_coreInstance;

	float m_LOD;
	vec2 m_instancesSize;
	LevelInstance*** m_instances;

	friend LevelInstance;
};