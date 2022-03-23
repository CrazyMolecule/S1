#pragma once

#include <iostream>
#include <memory>

namespace bavykin
{
	template<typename T>
	class List
	{
	protected:
		std::shared_ptr<T[]> m_List;
		int m_Size;
		int m_Count;

	public:
		List();
		List(int);
		List(List&) noexcept;
		List(List&&) noexcept;

		List& operator=(List&) noexcept;
		List& operator=(List&&) noexcept;
		T operator[](int);

		int getCount() noexcept;
		bool isEmpty() noexcept;
	};

	template<typename T>
	List<T>::List() : List(0) {}

	template<typename T>
	List<T>::List(int size)
	{
		if (size < 0)
		{
			throw std::length_error("List size out of range");
		}
		m_List = std::shared_ptr<T[]>(new T[size]);
		m_Size = size;
		m_Count = 0;
	}

	template<typename T>
	List<T>::List(List& value) noexcept : m_List(value.m_List), m_Size(value.m_Size), m_Count(value.m_Count) {}

	template<typename T>
	List<T>::List(List&& value) noexcept : m_List(std::move(value.m_List)), m_Size(value.m_Size), m_Count(value.m_Count)
	{
		value.m_Size = 0;
		value.m_Count = 0;
	}

	template<typename T>
	List<T>& List<T>::operator=(List& value) noexcept
	{
		m_List = value.m_List;
		m_Size = value.m_Size;
		m_Count = value.m_Count;

		return *this;
	}

	template<typename T>
	List<T>& List<T>::operator=(List&& value) noexcept
	{
		m_List = std::move(value.m_List);
		m_Size = value.m_Size;
		m_Count = value.m_Count;

		m_Size = value.m_Size;
		m_Count = value.m_Count;

		return *this;
	}

	template<typename T>
	T List<T>::operator[](int index)
	{
		if (index < 0 or index >= m_Size)
		{
			throw std::length_error("List size out of range");
		}
			
		return m_List[index];
	}

	template<typename T>
	int List<T>::getCount() noexcept
	{
		return m_Size;
	}

	template<typename T>
	bool List<T>::isEmpty() noexcept
	{
		return m_Count == 0;
	}
}