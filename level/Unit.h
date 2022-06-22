#pragma once
#include "Component.h"
#include "LocatedObject.h"
#include "other/LinkedList.h"

class Component;
class LocatedComponent;
class Level;
class LevelInstance;

class Unit
	: public Component
	, public virtual LocatedObject
{
public:
	Unit(LevelInstance* lvl);
	//Unit(Transform transform, Level* lvl);
	virtual ~Unit();

	void setUnitScale(const vec3 scale);
	void setUnitLocation(const vec3 location);
	void setUnitRotation(const vec3 rotation);
	void setUnitTransform(const Transform transform);
	void tick() override;
	void remove() = 0;

protected:
	void updateTreeTransform();
	LocatedComponent* getComponentTree() { return m_locatedComponentTree; }
	void attachLocatedComponent(LocatedObject *component, Transform relativeTransform);

private:
	using LocatedObject::setLocation;
	using LocatedObject::setRotation;
	using LocatedObject::setScale;
	using LocatedObject::setTransform;

	LocatedComponent *m_locatedComponentTree;
	LincedList<Component> m_logicalComponents;
	LevelInstance *m_levelInstance;
	friend class Level;
	friend class LevelInstance;
};