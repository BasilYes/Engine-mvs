#include "Level.h"
#include "Unit.h"
#include "LevelInstance.h"

Level* Level::m_activeLevel;
void Level::init(Level* lvl)
{
	ASSERT(!m_activeLevel, "Can't Lvl reinit");
	m_activeLevel = lvl;
}

void Level::initInstance()
{
	m_activeInstance = createLevelInstance(0.0f, 0.0f);
}

LevelInstance* Level::createLevelInstance(vec3 offset)
{
	return new LevelInstance(offset);
}

void Level::tick()
{
	m_activeInstance->tick();
}

Level::Level()
{
}

Level::~Level()
{
	delete m_activeInstance;
}