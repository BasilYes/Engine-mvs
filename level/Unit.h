#pragma once
#include "LogicalComponent.h"
#include "LocatedObject.h"
#include "other/LinkedList.h"

class LogicalComponent;
class LocatedComponent;
class Level;
class LevelInstance;

class Unit
	: public LogicalComponent
	, public virtual LocatedObject
{
public:
	Unit(LevelInstance* lvl);
	//Unit(Transform transform, Level* lvl);
	virtual ~Unit();

	LevelInstance* getLevelInstance() { return m_levelInstance; }

	void setUnitScale(const vec3 scale);
	void setUnitLocation(const vec3 location);
	void setUnitRotation(const vec3 rotation);
	void setUnitTransform(const Transform transform);
	void tick() override;
	virtual void attach(LevelInstance* instance);
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
	LincedList<LogicalComponent> m_logicalComponents;
	LincedListItem<Unit>* m_selfRef;
	LevelInstance *m_levelInstance;
	friend LevelInstance;
};