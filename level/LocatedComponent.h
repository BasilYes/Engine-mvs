#pragma once
#include "LocatedObject.h"
#include "other/math/matrix.h"
class Unit;
class LocatedComponent
{
	LocatedComponent(LocatedObject* object, LocatedObject* parent, LocatedComponent* right = nullptr, LocatedComponent* child = nullptr);
	~LocatedComponent();

	vec3 getRelativeScale() const { return m_relativeTransform.scale; }
	vec3 getRelativeLocation() const { return m_relativeTransform.location; }
	vec3 getRelativeRotation() const { return m_relativeTransform.rotation; }
	Transform getRelativeTransform() const { return m_relativeTransform; }
	void setRelativeScale(const vec3 scale);
	void setRelativeLocation(const vec3 location);
	void setRelativeRotation(const vec3 rotation);
	void setRelativeTransform(const Transform transform);
private:
	void refreshTreeTransform(const mat3& rotate, const Transform& trans);
	void refreshNodeTransform();

	LocatedObject* m_object;
	LocatedObject* m_parent;
	LocatedComponent* m_child;
	LocatedComponent* m_right;
	Transform m_relativeTransform;

	friend class Unit;
	LocatedComponent(LocatedComponent&&) = delete;
	LocatedComponent(LocatedComponent&) = delete;
	void operator=(LocatedComponent) = delete;
};