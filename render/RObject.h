#pragma once
#include "other/LinkedList.h"
class RCamera;
class RManager;
class RObject
{
public:
	RObject();
	virtual ~RObject();
private:
	virtual void draw(const RCamera* camera) const = 0;
	LincedListItem<const RObject>* m_selfRef;
	friend RManager;
};