#include <iostream>
#include <memory>

#ifndef LIST_H
#define LIST_H
namespace bavykin
{
	template<typename T>
	class List
	{
	public:
		List();
		List(const List&) noexcept;
		List(List&&) noexcept;
		List(int);

		List& operator=(const List&) noexcept;
		List& operator=(List&&) noexcept;
		T operator[](int) const;

		int getCount() const noexcept;
		bool isEmpty() const noexcept;

	protected:
		std::shared_ptr< T[] > m_List;
		int m_Size;
		int m_Count;
	};

	template<typename T>
	List< T >::List() : List(0) {}

	template<typename T>
	List< T >::List(int size)
	{
		if (size < 0)
		{
			throw std::length_error("List size out of range");
		}
		m_List = std::shared_ptr< T[] >(new T[size]);
		m_Size = size;
		m_Count = 0;
	}

	template<typename T>
	List< T >::List(const List& value) noexcept : m_List(value.m_List), m_Size(value.m_Size), m_Count(value.m_Count) {}

	template<typename T>
	List< T >::List(List&& value) noexcept : m_List(std::move(value.m_List)), m_Size(value.m_Size), m_Count(value.m_Count)
	{
		value.m_Size = 0;
		value.m_Count = 0;
	}

	template<typename T>
	List< T >& List< T >::operator=(const List& value) noexcept
	{
		m_List = value.m_List;
		m_Size = value.m_Size;
		m_Count = value.m_Count;

		return *this;
	}

	template<typename T>
	List< T >& List< T >::operator=(List&& value) noexcept
	{
		m_List = std::move(value.m_List);
		m_Size = value.m_Size;
		m_Count = value.m_Count;

		m_Size = value.m_Size;
		m_Count = value.m_Count;

		return *this;
	}

	template<typename T>
	T List< T >::operator[](int index) const
	{
		if (index < 0 or index >= m_Size)
		{
			throw std::length_error("List size out of range");
		}

		return m_List[index];
	}

	template<typename T>
	int List< T >::getCount() const noexcept
	{
		return m_Size;
	}

	template<typename T>
	bool List< T >::isEmpty() const noexcept
	{
		return m_Count == 0;
	}
}
#endif
