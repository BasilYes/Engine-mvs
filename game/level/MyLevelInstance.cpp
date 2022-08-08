#include "MyLevelInstance.h"
#include "game/render/LandscapeFragment.h"
#include "render/RManager.h"


MyLevelInstance::MyLevelInstance(vec3 offset, vec2 size, uvec2 position, Level* level)
	:LevelInstance(offset, size, position, level)
{
	LandscapeFragment* l_frag = new LandscapeFragment(Transform{ vec3{0.0f, 0.0f, 0.0f}, vec3{}, vec3{1.0f,1.0f,1.0f} }, offset, size[0], size[1], this);
	attachRObject(l_frag);
	attachObject(l_frag);
}
