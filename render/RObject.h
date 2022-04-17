#pragma once
#include "other/LinkedList.h"
class RCamera;
class RManager;
class RObject
{
public:
	RObject();
	virtual ~RObject();
	virtual void Draw(const RCamera* camera) const = 0;
private:
	LincedListItem<RObject>* m_selfRef;
	friend RManager;
};