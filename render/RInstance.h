#pragma once
#include "other/math/vector.h"
#include "other/LinkedList.h"
class RObject;
class RMesh;
class RCamera;
class LevelInstance;
class RInstance
{
public:
	RInstance(LevelInstance* ownInstance);
	~RInstance();
	void addRObject(RObject* mesh);
	void draw(RCamera* camera) const;
private:
	LevelInstance* m_ownInstance;
	LincedList<const RObject> m_drawList;
};

