#include "MyLevel.h"
#include "render/RManager.h"
#include "game/units/TestUnit.h"
#include "level/Mesh.h"
#include "game/render/LandscapeFragment.h"

MyLevel::MyLevel()
{
	TestUnit* unit = new TestUnit{ Transform{vec3{},vec3{}, vec3{1.0f,1.0f,1.0f}}, (Level*)this };
	//Mesh* mesh = new Mesh{ Transform{vec3{},vec3{}, vec3{1.0f,1.0f,1.0f}} , 0, 0 };
	//attachObject(mesh);
	LandscapeFragment* l_frag = new LandscapeFragment(Transform{ vec3{},vec3{}, vec3{1.0f,1.0f,1.0f} }, 5, 5);
	attachUnit(unit);
	attachObject(l_frag);
	RManager::getRManager()->addRObject(l_frag);
	RManager::getRManager()->addMesh(unit);
}