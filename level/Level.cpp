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
	m_coreInstance = createLevelInstance(vec3{ 0.0f, 0.0f, 0.0f });
	m_coreInstance->m_higherX = createLevelInstance(vec3{ 128.0f, 0.0f, 0.0f });
}

LevelInstance* Level::createLevelInstance(vec3 offset)
{
	return new LevelInstance(offset);
}

void Level::tick()
{
	m_coreInstance->tick();
}

Level::Level()
{
}

Level::~Level()
{
	delete m_coreInstance;
}