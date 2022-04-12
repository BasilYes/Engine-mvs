#pragma once
#include "math/vector.h"

struct Transform
{
	vec3 location;
	vec3 rotation;
	vec3 scale;
};

class LocatedObject
{
public:
	LocatedObject(Transform transform)
		: m_transform{ transform }
	{}
	vec3 getScale() { return m_transform.scale; }
	vec3 getLocation() { return m_transform.location; }
	vec3 getRotation() { return m_transform.rotation; }
	Transform getTransform() { return m_transform; }
	void setScale(const vec3    scale) { m_transform.scale = scale; }
	void setLocation(const vec3 location) { m_transform.location = location; }
	void setRotation(const vec3 rotation) { m_transform.rotation = rotation; }
	void setTransform(const Transform transform) { m_transform = transform; }

private:
	Transform m_transform;
};

