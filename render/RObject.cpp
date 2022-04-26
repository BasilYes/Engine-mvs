#include "RObject.h"
#include "RManager.h"
#include "other/LinkedList.h"

RObject::RObject()
{

}

RObject::~RObject()
{
	if (m_selfRef)
		LincedList<const RObject>::remove(m_selfRef);
}