#pragma once
#include "event/EEvent.h"
#include "EEvent.h"
class IManager
{
public:
	static IManager* getIManager() { return m_iManager; }
	static void init();
	static void processInput();
	static EEventCaller<float> moveForward;
	static EEventCaller<float> moveRight;
	static EEventCaller<float> moveUp;
private:
	IManager();
	static IManager* m_iManager;
};

