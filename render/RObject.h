#pragma once
#include "other/LinkedList.h"
class RCamera;
class RInstance;
class RObject
{
public:
	RObject();
	virtual ~RObject();
	virtual void draw(RCamera* camera) const = 0;
private:
	LincedListItem<const RObject>* m_selfRef;
	friend class RInstance;
	friend class RManager;
};