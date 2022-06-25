#pragma once
#include "render/renderable_object/RMesh.h"
class Mesh
	: public RMesh
{
public:
	Mesh(Transform transform, unsigned int modelKey, unsigned int shaderKey);
private:
	void draw(RCamera* camera) const override;
};

