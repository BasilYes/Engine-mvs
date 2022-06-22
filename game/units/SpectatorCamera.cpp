#include "SpectatorCamera.h"
#include "other/math/matrix.h"

SpectatorCamera::SpectatorCamera(Transform transform, Level* lvl)
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
}

void SpectatorCamera::MoveForaward::call(float axis)
{
	mat3 rotat; vec3 trans{0.0f, axis/10.0f, 0.0f};
	initRotateTransform(rotat, m_owner->getRotation());
	trans = rotat * trans;
	m_owner->setUnitLocation(m_owner->getLocation() + trans * 1.0f);
}

void SpectatorCamera::MoveRight::call(float axis)
{
	mat3 rotat; vec3 trans{ axis/10.0f, 0.0f, 0.0f };
	initRotateTransform(rotat, m_owner->getRotation());
	trans = rotat * trans;
	m_owner->setUnitLocation(m_owner->getLocation() + trans * 1.0f);
}

void SpectatorCamera::MoveUp::call(float axis)
{
	mat3 rotat; vec3 trans{ 0.0f, 0.0f, axis/10.0f };
	initRotateTransform(rotat, m_owner->getRotation());
	trans = rotat * trans;
	m_owner->setUnitLocation(m_owner->getLocation() + trans * 1.0f);
}
