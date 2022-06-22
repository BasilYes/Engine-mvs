#pragma once
#include "render/RObject.h"
#include "other/math/vector.h"
#include "level/LocatedObject.h"
#include "asset/AManager.h"
#include <vector>
struct vertex
{
	vec3 position;
	vec3 normal;
	//vec3 color;	
};
class LandscapeFragment
	: public RObject
	, public LocatedObject
{
public:
	LandscapeFragment(Transform transform, unsigned int sizeX, unsigned int sizeY);
	void setupSegment();
	void updateMesh();
private:
	unsigned int m_sizeX;
	unsigned int m_sizeY;
	unsigned int m_offsetX;
	unsigned int m_offsetY;
	std::vector<vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	ARef<AShader> m_shader;
	unsigned int VAO, VBO, EBO;
	void draw(const RCamera* camera) const override;
};