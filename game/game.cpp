#include "render/RManager.h"
#include "asset/AManager.h"
#include "game/level/MyLevel.h"


#include <debug.h>
int main()
{
	AManager::init();
	RManager::init();
	Level::init(new MyLevel{});
	while (true)
	{
		Level::getActiveLevel()->tick();
		if (!RManager::getRManager()->drawFrame())
			return 0;
	}
}