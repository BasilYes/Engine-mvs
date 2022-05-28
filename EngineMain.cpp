//#include "render/RManager.h"
//#include "asset/AManager.h"
//#include "level/Level.h"
//
//
//#include <debug.h>
//int main()
//{
//	AManager::init();
//	RManager::init();
//	Level::init();
//	while (true)
//	{
//		Level::getActiveLevel()->tick();
//		if (!RManager::getRManager()->drawFrame())
//			return 0;
//	}
//}


//#include "other/LinkedList.h"
//#include <iostream>
//
//int main()
//{
//	LincedList<char> list{};
//	list.pushBack(new char{ 'a' });
//	list.pushBack(new char{ 'b' });
//	list.pushBack(new char{ 'c' });
//	list.pushBack(new char{ 'd' });
//	LincedListItem<char>* item = list.getFirst();
//	while (item->getNext())
//	{
//		std::cout << **item;
//		if (**item == 'b')
//		{
//			item = item->getNext();
//			list.remove(item->getPrev());
//		}
//		else
//		{
//			item = item->getNext();
//		}
//	}
//	item = list.getFirst();
//	std::cout << "\n";
//	while (item->getNext())
//	{
//		std::cout << **item;
//		item = item->getNext();
//	}
//}