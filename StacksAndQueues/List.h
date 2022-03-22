#pragma once

#include <iostream>

namespace bavykin
{
	template<typename T>
	class List
	{
	private:
		void replaceList(List&) noexcept;

	protected:
		T* m_List;
		int m_Size;
		int m_Count;

	public:
		List();
		List(int);
		List(List&) noexcept;
		List(List&&);
		~List() noexcept;

		List& operator=(List&) noexcept;
		List& operator=(List&&);
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
		m_List = new T[size];
		m_Size = size;
		m_Count = 0;
	}

	template<typename T>
	List<T>::List(List& value) noexcept : m_Size(value.m_Size), m_Count(value.m_Count)
	{
		replaceList(value);
	}

	template<typename T>
	List<T>::List(List&& value) : m_List(value.m_List), m_Size(value.m_Size), m_Count(value.m_Count)
	{
		value.m_List = NULL;
		value.m_Size = NULL;
		value.m_Count = NULL;
	}

	template<typename T>
	List<T>::~List() noexcept
	{
		delete[] m_List;
	}

	template<typename T>
	List<T>& List<T>::operator=(List& value) noexcept
	{
		replaceList(value);

		m_Size = value.m_Size;
		m_Count = value.m_Count;

		return *this;
	}

	template<typename T>
	List<T>& List<T>::operator=(List&& value)
	{
		m_List = value.m_List;
		m_Size = value.m_Size;
		m_Count = value.m_Count;

		value.m_List = NULL;
		value.m_Size = NULL;
		value.m_Count = NULL;
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

	template<typename T>
	void List<T>::replaceList(List& value) noexcept
	{
		delete[] m_List;
		m_List = nullptr;

		m_List = new T[value.m_Size];
		for (size_t i = 0; i < m_Count; i++)
		{
			m_List[i] = value.m_List[i];
		}
	}
}