#pragma once
#include "other/math/matrix.h"
#include "level/LocatedObject.h"
class RManager;
class RCamera
	: public LocatedObject
{
public:
	RCamera(Transform transform)
		: LocatedObject(transform)
	{}

	mat4 getViewMatrix() const { return m_viewMatrix; }
	void updateViewMatrix(const RManager* manager);
private:
	mat4 m_viewMatrix;
};