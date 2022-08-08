#pragma once
#include "level/LevelInstance.h"
#include "other/math/vector.h"
class MyLevelInstance :
    public LevelInstance
{
public:
    MyLevelInstance(vec3 offset, vec2 size, uvec2 position, Level* level);
    
};

