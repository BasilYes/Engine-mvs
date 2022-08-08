#pragma once
#include "level/LogicalComponent.h"
class MovementComponent
	:public LogicalComponent
{
protected:
	Unit *m_owner;
};