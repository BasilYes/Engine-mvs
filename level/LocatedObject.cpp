#include "LocatedComponent.h"
#include "Level.h"

LocatedObject::LocatedObject(Transform transform, Level* lvl)
	: m_transform{ transform }
{
	lvl->attachObject(this);
}