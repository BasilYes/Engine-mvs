#include "Unit.h"
#include "LocatedComponent.h"
#include "Component.h"

Unit::~Unit()
{
	auto item = m_logicalComponents.getFirst();
	while (item)
	{
		delete item->getContent();
		item = item->getNext();
	}
}

void Unit::setActorScale(const vec3 scale)
{
	setScale(scale);
	m_locatedComponentTree->refreshNodeTransform();
}

void Unit::setActorLocation(const vec3 location)
{
	setLocation(location);
	m_locatedComponentTree->refreshNodeTransform();
}

void Unit::setActorRotation(const vec3 rotation)
{
	setRotation(rotation);
	m_locatedComponentTree->refreshNodeTransform();
}

void Unit::setActorTransform(const Transform transform)
{
	setTransform(transform);
	m_locatedComponentTree->refreshNodeTransform();
}

void Unit::tick()
{
	LincedListItem<Component>* item = m_logicalComponents.getFirst();
	while (item)
	{
		item->getContent()->tick();
		item = item->getNext();
	}
}

