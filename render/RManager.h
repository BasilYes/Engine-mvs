#pragma once
#include "other/math/vector.h"
#include "other/LinkedList.h"
struct GLFWwindow;
class RCamera;
class Mesh;


class RManager
{
public:
	static void init();
	static RManager* getRManager() { return m_rManager; }

	bool drawFrame();
	vec2 getWindowSize() { return m_windowSize; }
	RCamera* getActiveCamera() { return m_activeCamera; }
private:
	static RManager* m_rManager;

	static GLFWwindow* m_window;
	static vec2 m_windowSize;

	RCamera* m_activeCamera;
	LincedList<Mesh> m_meshList;


	RManager();
	~RManager();
	void createWindow();
};

