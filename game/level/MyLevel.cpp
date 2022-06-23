#include "MyLevel.h"
#include "render/RManager.h"
#include "MyLevelInstance.h"

//#include "game/units/TestUnit.h"
//#include "level/Mesh.h"
//#include "game/render/LandscapeFragment.h"
#include "game/units/SpectatorCamera.h"

MyLevel::MyLevel()
	: Level()
{
	initInstance();
	//TestUnit* unit = new TestUnit{ Transform{vec3{},vec3{}, vec3{1.0f,1.0f,1.0f}}, this };
	//attachUnit(unit);
	//RManager::getRManager()->addMesh(unit);
	
	//Mesh* mesh = new Mesh{ Transform{vec3{},vec3{}, vec3{1.0f,1.0f,1.0f}} , 1, 1 };
	//attachObject(mesh);
	//RManager::getRManager()->addMesh(mesh);
	SpectatorCamera* cam = new SpectatorCamera{ Transform{}, getCoreInstance() };
	getCoreInstance()->attachUnit(cam);
	RManager::getRManager()->setActiveCamera(cam);

	//LandscapeFragment* l_frag = new LandscapeFragment(Transform{ vec3{},vec3{0.0f, 0.0f, 0.0f}, vec3{1.0f,1.0f,1.0f} }, 512, 512);
	//getActiveInstance()->attachObject(l_frag);
	//RManager::getRManager()->addRObject(l_frag);
}

LevelInstance* MyLevel::createLevelInstance(vec3 offset)
{
	return new MyLevelInstance(offset);
}
