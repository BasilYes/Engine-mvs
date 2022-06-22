#pragma once
#include "level/Level.h"
class MyLevel
	: public Level
{
public:
	MyLevel();
	LevelInstance* createLevelInstance(vec3 offset) override;
};