#pragma once
class AManager;
class AShader;
class AModel;

template<typename Type>
class ARef
{
public:
	Type& operator*()  const { return *m_ref; }
	Type* operator->() const { return  m_ref; }
	ARef(ARef&& r)
		: m_ref{ r.m_ref }, m_count{ r.m_count }, m_key{ r.m_key }
	{
		(*m_count)++;
	}
	~ARef();
private:
	unsigned int* m_count;
	unsigned int m_key;
	Type* m_ref;
	ARef(ARef& r)
		:m_count{ r.m_count }, m_ref{ r.m_ref }, m_key{ r.m_key }
	{
		(*m_count)++;
	}
	ARef(Type* ref, unsigned int key)
		:m_count{ new unsigned int{0} }, m_ref{ ref }, m_key{ key }
	{
	}

	void operator=(ARef) = delete;
	friend class AManager;
};