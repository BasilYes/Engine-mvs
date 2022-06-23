#pragma once
#include "other/math/matrix.h"
#include "level/LocatedObject.h"
class RManager;
class RCamera
	: public virtual LocatedObject
{
public:
	RCamera(Transform transform)
		: LocatedObject(transform)
	{}
	RCamera()
		: LocatedObject(Transform{})
	{}

	mat4 getViewMatrix() const { return m_viewMatrix; }
	void updateViewMatrix(vec3 location, vec3 rotation);
private:
	mat4 m_viewMatrix;
};