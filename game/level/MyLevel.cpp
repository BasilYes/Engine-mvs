#include "MyLevel.h"
#include "render/RManager.h"
#include "game/units/TestUnit.h"
#include "level/Mesh.h"

MyLevel::MyLevel()
{
	TestUnit* unit = new TestUnit{ Transform{vec3{},vec3{}, vec3{1.0f,1.0f,1.0f}}, (Level*)this };
	//Mesh* mesh = new Mesh{ Transform{vec3{},vec3{}, vec3{1.0f,1.0f,1.0f}} , 0, 0 };
	//attachObject(mesh);
	attachUnit(unit);
	RManager::getRManager()->addMesh(unit);
}