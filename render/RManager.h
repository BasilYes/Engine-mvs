#pragma once
#include "other/math/vector.h"
#include "other/LinkedList.h"
struct GLFWwindow;
class RCamera;
class RObject;
class RMesh;


class RManager
{
public:
	static void init();
	static RManager* getRManager() { return m_rManager; }

	bool drawFrame() const;
	vec2 getWindowSize() const { return m_windowSize; }
	RCamera* getActiveCamera() const { return m_activeCamera; }
	void addMesh(RMesh* mesh);
private:
	static RManager* m_rManager;

	static GLFWwindow* m_window;
	static vec2 m_windowSize;

	RCamera* m_activeCamera;
	LincedList<const RObject> m_drawList;

	RManager();
	~RManager();
	void createWindow();
};

