#pragma once
#include "level/Unit.h"
#include "render/renderable_object/RMesh.h"
class TestUnit
	: public Unit
	, public RMesh
{
public:
	static TestUnit* u;
	TestUnit(Transform transform, LevelInstance* lvl);
private:
	void draw(RCamera* camera) const override;
};