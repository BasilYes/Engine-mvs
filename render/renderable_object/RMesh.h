#pragma once
#include <vector>
#include "asset/AManager.h"
#include "level/LocatedObject.h"
#include "other/math/matrix.h"
#include "render/RObject.h"

class RManager;

class RMesh
	: public virtual LocatedObject
	, public RObject
{
public:
	RMesh(unsigned int modelKey, unsigned int shaderKey);
	RMesh(unsigned int modelKey, std::vector<unsigned int> shadersKeys);
protected:
	void draw(RCamera* camera) const override = 0;
private:
	std::vector<ARef<AShader>> m_shaders;
	ARef<AModel> m_model;

	friend class RManager;
};