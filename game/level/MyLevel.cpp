#include "MyLevel.h"
#include "render/RManager.h"
#include "game/units/TestUnit.h"
#include "level/Mesh.h"
#include "game/render/LandscapeFragment.h"

MyLevel::MyLevel()
{
	TestUnit* unit = new TestUnit{ Transform{vec3{},vec3{}, vec3{1.0f,1.0f,1.0f}}, (Level*)this };
	attachUnit(unit);
	RManager::getRManager()->addMesh(unit);
	
	//Mesh* mesh = new Mesh{ Transform{vec3{},vec3{}, vec3{1.0f,1.0f,1.0f}} , 1, 1 };
	//attachObject(mesh);
	//RManager::getRManager()->addMesh(mesh);

	LandscapeFragment* l_frag = new LandscapeFragment(Transform{ vec3{},vec3{0.0f, 0.0f, 0.0f}, vec3{1.0f,1.0f,1.0f} }, 6, 6);
	attachObject(l_frag);
	RManager::getRManager()->addRObject(l_frag);
}