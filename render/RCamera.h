#pragma once
#include "other/math/matrix.h"
#include "other/LocatedObject.h"
class RCamera
	: public LocatedObject
{
public:
	RCamera(Transform transform)
		: LocatedObject(transform)
	{}

	void initViewMatrix(mat4& mat);
};