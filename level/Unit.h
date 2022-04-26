#pragma once
#include "Component.h"
#include "LocatedObject.h"
#include "other/LinkedList.h"
class Component;
class LocatedComponent;
class Level;

class Unit
	: public virtual Component
	, public virtual LocatedObject
{
	Unit(Transform);
	virtual ~Unit();

	void setActorScale(const vec3 scale);
	void setActorLocation(const vec3 location);
	void setActorRotation(const vec3 rotation);
	void setActorTransform(const Transform transform);
	void tick() override;
	void remove() override {}

private:
	using LocatedObject::setLocation;
	using LocatedObject::setRotation;
	using LocatedObject::setScale;
	using LocatedObject::setTransform;

	LocatedComponent* m_locatedComponentTree;
	LincedList<Component> m_logicalComponents;
	friend class Level;
};

