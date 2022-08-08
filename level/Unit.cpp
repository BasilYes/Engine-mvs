#include "Unit.h"
#include "LocatedComponent.h"
#include "level/LevelInstance.h"

Unit::Unit(LevelInstance* lvl)
	: m_levelInstance{ lvl }
	, m_locatedComponentTree{ nullptr }
{}
//Unit::Unit(Transform transform, Level* lvl)
//	: LocatedObject(transform)
//	, m_Level{lvl}
//	, m_locatedComponentTree{nullptr}
//{
//}

Unit::~Unit()
{
	auto item = m_logicalComponents.getFirst();
	while (item)
	{
		delete item->getContent();
		item = item->getNext();
	}
}

void Unit::updateTreeTransform()
{
	auto node = m_locatedComponentTree;
	while (node)
	{
		m_locatedComponentTree->refreshNodeTransform();
		node = node->m_right;
	}
}

void Unit::attachLocatedComponent(LocatedObject *component, Transform relativeTransform)
{
	if (m_locatedComponentTree)
	{
		auto node = m_locatedComponentTree;
		while (node->m_right)
			node = node->m_right;
		node->m_right = new LocatedComponent{ component, relativeTransform,  this };
	}
	else
		m_locatedComponentTree = new LocatedComponent{ component, relativeTransform,  this};
}

void Unit::setUnitScale(const vec3 scale)
{
	setScale(scale);
	updateTreeTransform();
}

void Unit::setUnitLocation(const vec3 location)
{
	setLocation(location);
	if (m_levelInstance->updateUnitLocation(this))
		return;
	updateTreeTransform();
}

void Unit::setUnitRotation(const vec3 rotation)
{
	setRotation(rotation);
	updateTreeTransform();
}

void Unit::setUnitTransform(const Transform transform)
{
	setTransform(transform);
	updateTreeTransform();
}

void Unit::tick()
{
	LincedListItem<LogicalComponent>* item = m_logicalComponents.getFirst();
	while (item)
	{
		item->getContent()->tick();
		item = item->getNext();
	}
}

void Unit::remove()
{
	LincedList<Unit>::remove(m_selfRef);
}

void Unit::attach(LevelInstance* instance)
{
	m_levelInstance = instance;
}
