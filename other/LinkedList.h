#pragma once
#include "debug.h"
template<typename Type>
class LincedList;

template<typename Type>
class LincedListItem
{
public:
	Type* getContent() const { return m_item; }
	LincedListItem<Type>* getNext() const { return m_next; }
	LincedListItem<Type>* getPrev() const { return m_prev; }
private:
	LincedListItem<Type>* m_next;
	LincedListItem<Type>* m_prev;
	Type* m_item;
	LincedListItem(Type* item, LincedListItem<Type>* prev, LincedListItem<Type>* next)
		: m_item{item}, m_next{next}, m_prev{prev}
	{}
	LincedListItem(LincedListItem&) = delete;
	LincedListItem(LincedListItem&&) = delete;
	void operator=(LincedListItem) = delete;
	friend LincedList<Type>;
};

template<typename Type>
class LincedList
{
public:
	LincedList()
	{
		begin = new LincedListItem<Type>{ nullptr, nullptr, nullptr };
	}
	LincedListItem<Type>* getFirst() const { return begin->m_next; }
	LincedListItem<Type>* getBegin() const { return begin; }

	static void pushBack(Type* item, LincedListItem<Type>* list)
	{
		list->m_prev = new LincedListItem<Type>{ item, list->m_prev, list };
		if (list->m_prev->m_prev)
			list->m_prev->m_prev->m_next = list->m_prev;
	}
	void pushFront(Type* item)
	{
		begin->m_next = new LincedListItem<Type>{ item, begin, begin->m_next };
		if (begin->m_next->m_next)
			begin->m_next->m_next->m_prev = begin->m_next;
	}
	static void pushFront(Type* item, LincedListItem<Type>* list)
	{
		list->m_next = new LincedListItem<Type>{ item, list, list->m_next };
		if (list->m_next->m_next)
			list->m_next->m_next->m_prev = list->m_next;
	}
	static void remove(LincedListItem<Type>* item)
	{
		ASSERT(item->m_prev, "You can't remove begin of list")
		if (item->m_next)
			item->m_next->m_prev = item->m_prev;
		if (item->m_prev)
			item->m_prev->m_next = item->m_next;
		delete item;
	}
	~LincedList()
	{
		LincedListItem<Type>* item = begin;
		while (item->m_next)
		{
			item = item->m_next;
			delete item->m_prev;
		}
		delete item;
	}
private:
	LincedListItem<Type>* begin;
};