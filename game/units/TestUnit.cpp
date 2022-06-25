#include "TestUnit.h"
#include "level/Mesh.h"
#include "level/LocatedComponent.h"
#include "render/RManager.h"
TestUnit* TestUnit::u;
TestUnit::TestUnit(Transform transform, LevelInstance* lvl)
	: Unit(lvl)
	, LocatedObject{transform}
	, RMesh{ 2, 1 }
{
	u = this;
	//Mesh* mesh = new Mesh{ Transform{}, 0, 1 };
	//attachLocatedComponent(mesh, Transform{ Transform{vec3{4.0f, 0.0f,0.0f},vec3{}, vec3{1.0f,1.0f,1.0f}} });
	//RManager::getRManager()->addMesh(mesh);
	updateTreeTransform();
}

void TestUnit::draw(RCamera* camera) const
{
	RMesh::draw(camera);
}