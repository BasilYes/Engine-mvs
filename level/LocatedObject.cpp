#include "LocatedComponent.h"
#include "LevelInstance.h"

LocatedObject::LocatedObject(Transform transform, LevelInstance* lvl)
	: m_transform{ transform }
{
	lvl->attachObject(this);
}