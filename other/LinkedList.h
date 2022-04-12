#pragma once
template<typename Type>
class LincedList;

template<typename Type>
class LincedListItem
{
public:
	Type& operator*()  const { return *m_item; }
	Type* operator->() const { return m_item; }
	LincedListItem<Type>* getNext() { return m_next; }
	LincedListItem<Type>* getPrev() { return m_prev; }
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
	LincedListItem<Type>* getFirst() { return first->m_next; }
	LincedListItem<Type>* getLast() { return last->m_prev; }

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