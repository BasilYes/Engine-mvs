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
	: public LocatedObject
	, public RObject
{
public:
	LandscapeFragment(Transform transform, vec3 offset, unsigned int sizeX, unsigned int sizeY);
	~LandscapeFragment();
	void setupSegment();
	void updateMesh();
private:
	unsigned int m_sizeX;
	unsigned int m_sizeY;
	vec3 m_offset;
	std::vector<vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	ARef<AShader> m_shader;
	unsigned int VAO, VBO, EBO;
	void draw(RCamera* camera) const override;
};