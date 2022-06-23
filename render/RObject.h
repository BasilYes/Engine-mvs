#pragma once
#include "other/LinkedList.h"
class RCamera;
class RInstance;
class RObject
{
public:
	RObject();
	virtual ~RObject();
private:
	virtual void draw(const RCamera* camera) const = 0;
	LincedListItem<const RObject>* m_selfRef;
	friend class RInstance;
};