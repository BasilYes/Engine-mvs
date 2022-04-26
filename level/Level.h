#pragma once
#include "other/LinkedList.h"
class LocatedObject;
class Unit;
class Level
{
public:

	static void init();
	static Level* getActiveLevel() { return m_activeLevel; }
	void tick();

	template<typename Type, typename ...Args>
	void createObject(Args... args)
	{
		m_objects.pushFront(new Type{ args... });
	}
	template<typename Type, typename ...Args>
	void spawnActor(Args... args)
	{
		m_units.pushFront(new Type{ args... });
	}
	Level();
	~Level();
private:
	static Level* m_activeLevel;
	LincedList<LocatedObject> m_objects;
	LincedList<Unit> m_units;
};