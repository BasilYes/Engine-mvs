#include "MyLevelInstance.h"
#include "game/render/LandscapeFragment.h"
#include "render/RManager.h"


MyLevelInstance::MyLevelInstance(vec3 offset)
	:LevelInstance(offset)
{
	LandscapeFragment* l_frag = new LandscapeFragment(Transform{ vec3{},vec3{0.0f, 0.0f, 0.0f}, vec3{1.0f,1.0f,1.0f} }, 128, 128);
	attachObject(l_frag);
	RManager::getRManager()->addRObject(l_frag);
}
