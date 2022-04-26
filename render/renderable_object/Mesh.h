#pragma once
#include <vector>
#include "asset/AManager.h"
#include "level/LocatedObject.h"
#include "other/math/matrix.h"
#include "render/RObject.h"

class RManager;

class Mesh
	: public virtual LocatedObject
	, public RObject
{
public:
	Mesh(Transform transform, unsigned int modelKey, unsigned int shaderKey);
	Mesh(Transform transform, unsigned int modelKey, std::vector<unsigned int> shadersKeys);
private:
	std::vector<ARef<AShader>> m_shaders;
	ARef<AModel> m_model;

	virtual void draw(const RCamera* camera) const override;
	friend class RManager;
};