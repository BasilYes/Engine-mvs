#include "MyLevel.h"
#include "render/RManager.h"
#include "MyLevelInstance.h"

//#include "game/units/TestUnit.h"
//#include "level/Mesh.h"
//#include "game/render/LandscapeFragment.h"
#include "game/units/SpectatorCamera.h"

MyLevel::MyLevel()
	: Level(uvec2{16, 16}, vec2{128.0f, 128.0f}, 2.6f)
{
}

void MyLevel::load()
{
	Level::load();
	
	updateCoreInstanse(uvec2{ 0,0 });

	SpectatorCamera* cam = new SpectatorCamera{ Transform{vec3{64.0f, 64.0f, 100.0f}, vec3{}, vec3{1.0f,1.0f,1.0f}}, getCoreInstance() };
	getCoreInstance()->attachUnit(cam);
	RManager::getRManager()->setActiveCamera(cam);
}

LevelInstance* MyLevel::createLevelInstance(vec3 offset, vec2 size, uvec2 position)
{
	return new MyLevelInstance(offset, size, position, this);
}
