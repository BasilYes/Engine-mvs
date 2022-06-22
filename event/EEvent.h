#pragma once
#include "other/LinkedList.h"
#include <debug.h>

template<typename ...Args>
class EEvent;

template<typename ...Args>
class EEventCaller
{
public:
	EEventCaller()
		: m_eventList{}
	{}
	void bindEvent(EEvent<Args...>* event);
	void unbindEvent(EEvent<Args...>* event);
	void call(Args...) const;
private:
	LincedList<EEvent<Args...>> m_eventList;
	EEventCaller(EEventCaller&) = delete;
	EEventCaller(EEventCaller&&) = delete;
	void operator=(EEventCaller) = delete;
};

template<typename ...Args>
class EEvent
{
public:
	EEvent()
	{
	}
	EEvent( EEventCaller<Args...>* caller)
	{
		caller->bindEvent(this);
	}
	~EEvent()
	{
		if (m_caller)
			m_caller->unbindEvent(this);
	}
	virtual void call(Args... args) = 0;
private:
	void* m_obj;
	void (*m_func)(Args... args);
	EEventCaller<Args...>* m_caller;
	friend class EEventCaller<Args...>;
};

template<typename ...Args>
void EEventCaller<Args...>::bindEvent(EEvent<Args...>* event)
{
	ASSERT(!event->m_caller, "One event can't have more than one caller");
	m_eventList.pushFront(event);
	event->m_caller = this;
}

template<typename ...Args>
void EEventCaller<Args...>::unbindEvent(EEvent<Args...>* event)
{
	LincedListItem<EEvent<Args...>>* item = m_eventList.getFirst();
	while (item)
	{
		if (item->getContent() == event)
		{
			LincedList<EEvent<Args...>>::remove(item);
			event->m_caller = nullptr;
			break;
		}
		item = item->getNext();
	}
}

template<typename ...Args>
void EEventCaller<Args...>::call(Args... args) const
{
	LincedListItem<EEvent<Args...>>* item = m_eventList.getFirst();
	while(item)
	{
		item->getContent()->call(args...);
		item = item->getNext();
	}
}