#include "Level.h"
#include "Unit.h"
#include "LevelInstance.h"

////////////////
#include "game/units/SpectatorCamera.h"
#include "render/RManager.h"

Level* Level::m_activeLevel;
void Level::init(Level* lvl)
{
	ASSERT(!m_activeLevel, "Can't Lvl reinit");
	m_activeLevel = lvl;
	lvl->load();
}

void Level::load()
{
	m_coreInstance = createLevelInstance(vec3{ 0.0f, 0.0f, 0.0f }, vec2{128.0f, 128.0f});
}

void Level::updateCoreInstanse(LevelInstance* newInstance)
{
	m_coreInstance = newInstance;
	m_coreInstance->updateCoreInstanse();
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
	/////////////////////delete m_coreInstance;
}