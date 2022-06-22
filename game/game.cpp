#include "render/RManager.h"
#include "asset/AManager.h"
#include "game/level/MyLevel.h"
#include "event/IManager.h"

#include <debug.h>
int main()
{
	AManager::init();
	RManager::init();
	Level::init(new MyLevel{});
	IManager::init();
	while (true)
	{
		IManager::processInput();
		Level::getActiveLevel()->tick();
		if (!RManager::getRManager()->drawFrame())
			return 0;
	}
}