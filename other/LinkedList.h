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
	LincedList<Type>* m_list;
	LincedListItem<Type>* m_next;
	LincedListItem<Type>* m_prev;
	Type* m_item;
	LincedListItem(Type* item, LincedList<Type>* list, LincedListItem<Type>* prev, LincedListItem<Type>* next)
		: m_item{item}, m_list{list}, m_next{next}, m_prev{prev}
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
		last = new LincedListItem<Type>{ nullptr, this, nullptr, nullptr };
		first = new LincedListItem<Type>{ nullptr, this, nullptr, last };
		last->m_prev = first;
	}
	LincedListItem<Type>* getFirst() const { return first->m_next; }
	LincedListItem<Type>* getLast() const { return last->m_prev; }
	LincedListItem<Type>* getEnd() const { return last; }
	LincedListItem<Type>* getBegin() const { return first; }

	void pushBack(Type* item)
	{
		last->m_prev = new LincedListItem<Type>{ item, this, last->m_prev, last };
		last->m_prev->m_prev->m_next = last->m_prev;
	}
	void pushFront(Type* item)
	{
		first->m_next = new LincedListItem<Type>{ item, this, first, first->m_next };
		first->m_next->m_next->m_prev = first->m_next;
	}

	void remove(LincedListItem<Type>* item)
	{
		ASSERT(item->m_next && item->m_prev, "You can't remove begin or end of list")
		if(!item->m_next && !item->m_prev )
			if (item->m_next)
				item->m_next->m_prev = item->m_prev;
			if (item->m_prev)
				item->m_prev->m_next = item->m_next;
			if (item->m_item)
				delete item->m_item;
			delete item;
	}
private:
	LincedListItem<Type>* first;
	LincedListItem<Type>* last;
};