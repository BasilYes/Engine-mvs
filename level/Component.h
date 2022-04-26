#pragma once
class Unit;
class Component
{
protected:
	virtual void tick() = 0;
	virtual void remove() = 0;
	friend class Unit;
};