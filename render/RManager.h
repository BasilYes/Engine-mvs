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
	static vec2 getWindowSize() { return m_windowSize; }
	static void setWindowSize(vec2 windowSize) { m_windowSize = windowSize; }
	static GLFWwindow* getWindow() { return m_window; }
	RCamera* getActiveCamera() const { return m_activeCamera; }
	void setActiveCamera(RCamera* camera) { m_activeCamera = camera; }
	void addMesh(RMesh* mesh);
	void addRObject(RObject* mesh);
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

