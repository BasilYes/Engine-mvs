#pragma once
class Unit;
class LogicalComponent
{
protected:
	virtual void tick() = 0;
	virtual void remove() = 0;
	friend class Unit;
};
LogicalComponent;