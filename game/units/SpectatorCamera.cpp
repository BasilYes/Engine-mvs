#include "SpectatorCamera.h"
#include "other/math/matrix.h"

SpectatorCamera::SpectatorCamera(Transform transform, LevelInstance* lvl)
	: Unit(lvl)
	, LocatedObject{ transform }
	, RCamera{}
	, m_moveForward{this}
	, m_moveRight{this}
	, m_moveUp{this}
{
}

void SpectatorCamera::remove()
{
	Unit::remove();
}

void SpectatorCamera::attach(LevelInstance* instance)
{
	Unit::attach(instance);
	Level::getActiveLevel()->updateCoreInstanse(instance);
}

void SpectatorCamera::MoveForaward::call(float axis)
{
	mat3 rotat; vec3 trans{0.0f, axis/5.0f, 0.0f};
	initRotateTransform(rotat, m_owner->getRotation());
	trans = rotat * trans;
	m_owner->setUnitLocation(m_owner->getLocation() + trans * 1.0f);
}

void SpectatorCamera::MoveRight::call(float axis)
{
	mat3 rotat; vec3 trans{ axis/5.0f, 0.0f, 0.0f };
	initRotateTransform(rotat, m_owner->getRotation());
	trans = rotat * trans;
	m_owner->setUnitLocation(m_owner->getLocation() + trans * 1.0f);
}

void SpectatorCamera::MoveUp::call(float axis)
{
	mat3 rotat; vec3 trans{ 0.0f, 0.0f, axis/5.0f };
	initRotateTransform(rotat, m_owner->getRotation());
	trans = rotat * trans;
	m_owner->setUnitLocation(m_owner->getLocation() + trans * 1.0f);
}
