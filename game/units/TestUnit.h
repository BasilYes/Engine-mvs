#pragma once
#include "level/Unit.h"
#include "render/renderable_object/RMesh.h"
class TestUnit
	: public Unit
	, public RMesh
{
public:
	static TestUnit* u;
	TestUnit(Transform transform, Level* lvl);
private:
	void draw(const RCamera* camera) const override;
	void remove() override;
};