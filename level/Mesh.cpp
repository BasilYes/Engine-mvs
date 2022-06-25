#include "Mesh.h"

Mesh::Mesh(Transform transform, unsigned int modelKey, unsigned int shaderKey)
	: RMesh{ modelKey, shaderKey }
	, LocatedObject{ transform }
{
}

void Mesh::draw(RCamera* camera) const
{
	RMesh::draw(camera);
}