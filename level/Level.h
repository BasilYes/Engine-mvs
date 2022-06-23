#pragma once
#include "other/LinkedList.h"
#include "other/math/vector.h"
class LocatedObject;
class Unit;
class LevelInstance;
class Level
{
public:

	static void init(Level* lvl);
	static Level* getActiveLevel() { return m_activeLevel; }
	void initInstance();
	virtual LevelInstance* createLevelInstance(vec3 offset);
	LevelInstance* getCoreInstance() { return m_coreInstance; }
	void tick();

	Level();
	virtual ~Level();
private:
	static Level* m_activeLevel;
	LevelInstance* m_coreInstance;
};