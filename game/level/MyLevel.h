#pragma once
#include "level/Level.h"
class MyLevel
	: public Level
{
public:
	MyLevel();
	void load() override;
	LevelInstance* createLevelInstance(vec3 offset, vec2 size) override;
};