#pragma once
#include "other/math/vector.h"
struct GLFWwindow;
class RCamera;


class RManager
{
public:
	static void init();
	static bool drawFrame();
	static vec2 getWindowSize() { return m_windowSize; }
	static RManager* getRManager() { return m_rManager; }
	RCamera* getActiveCamera() { return m_activeCamera; }
private:
	static RManager* m_rManager;

	static GLFWwindow* m_window;
	static vec2 m_windowSize;

	RCamera* m_activeCamera;

	RManager();
	~RManager();
	void createWindow();
};

