#pragma once
#include <vector>
#include "asset/AManager.h"
#include "other/LocatedObject.h"
#include "other/math/matrix.h"

class RManager;

class Mesh
	: public LocatedObject
{
public:
	Mesh(Transform transform, unsigned int modelKey, unsigned int shaderKey);
	Mesh(Transform transform, unsigned int modelKey, std::vector<unsigned int> shadersKeys);
private:
	std::vector<ARef<AShader>> m_shaders;
	ARef<AModel> m_model;

	void Draw(const mat4& view);
	friend class RManager;
};