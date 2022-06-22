#pragma once
#include "level/Unit.h"
#include "render/RCamera.h"
#include "event/IManager.h"
class SpectatorCamera
	: public RCamera
	, public Unit
{
public:
	SpectatorCamera(Transform transform, LevelInstance* lvl);
private:
	void remove() override;
	class MoveForaward : public EEvent<float>
	{
	public:
		MoveForaward(SpectatorCamera* owner)
			:EEvent<float>{&IManager::moveForward}, m_owner{owner}
		{}
		void call(float axis) override;
	private:
		SpectatorCamera* m_owner;
	} m_moveForward;
	class MoveRight : public EEvent<float>
	{
	public:
		MoveRight(SpectatorCamera* owner)
			:EEvent<float>{ &IManager::moveRight }, m_owner{ owner }
		{}
		void call(float axis) override;
	private:
		SpectatorCamera* m_owner;
	} m_moveRight;
	class MoveUp : public EEvent<float>
	{
	public:
		MoveUp(SpectatorCamera* owner)
			:EEvent<float>{ &IManager::moveUp }, m_owner{ owner }
		{}
		void call(float axis) override;
	private:
		SpectatorCamera* m_owner;
	} m_moveUp;
};