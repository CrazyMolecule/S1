#include <iostream>

#include "Queue.h"

// null constructor
template<typename T>
Queue<T>::Queue() : Queue(0) {}

// default constructor
template<typename T>
Queue<T>::Queue(int size) : m_Size(size), m_Queue(new T[size]), m_Count(0) 
{
	std::cout << __FUNCTION__ << "(int size)" << std::endl;
}

// copy constructor
template<typename T>
Queue<T>::Queue(Queue& value) : m_Size(value.m_Size), m_Count(value.m_Count) 
{
	std::cout << __FUNCTION__ << "(Queue& value)" << std::endl;
	delete m_Queue;
	m_Queue = new T(*value.m_Queue);
}

// move constructor
template<typename T>
Queue<T>::Queue(Queue&& value) : m_Size(value.m_Size), m_Queue(value.m_Queue), m_Count(value.m_Count)
{
	std::cout << __FUNCTION__ << "(Queue&& value)" << std::endl;
	value.m_Queue = NULL;
	value.m_Size = NULL;
	value.m_Count = NULL;
}

// destructor
template<typename T>
Queue<T>::~Queue()
{
	std::cout << __FUNCTION__ << "" << std::endl;
	delete[] m_Queue;
}

// default assignment operator
template<typename T>
Queue<T>& Queue<T>::operator=(T value[])
{
	/*std::cout << __FUNCTION__ << std::endl;
	m_Size = sizeof(value) / sizeof(T);
	m_Queue = new T[m_Size];
	for (size_t i = 0; i < m_Size; i++)
		m_Queue[i] = value[i];

	return *this;*/
}

// copy assignment operator
template<typename T>
Queue<T>& Queue<T>::operator=(Queue& value)
{
	std::cout << __FUNCTION__ << "(Queue& value)" << std::endl;
	delete m_Queue;
	m_Queue = new T(*value.m_Queue);
	m_Size = value.m_Size;
	m_Count = value.m_Count;
	return *this;
}

// move assignment operator
template<typename T>
Queue<T>& Queue<T>::operator=(Queue&& value)
{
	std::cout << __FUNCTION__ << "(Queue&& value)" << std::endl;
	m_Size = value.m_Size;
	m_Queue = value.m_Queue;
	m_Count = value.m_Count;

	value.m_Queue = NULL;
	value.m_Size = NULL;
	value.m_Count = NULL;
	return *this;
}

template<typename T>
Queue<T> Queue<T>::operator+(Queue& other)
{
	int count = m_Count + other.m_Count;
	T* temporary = new T[m_Size + other.m_Size];

	for (size_t i = 0; i < m_Count; i++)
		temporary[i] = m_Queue[i];
	for (size_t i = m_Count; i < count; i++)
		temporary[i] = other.m_Queue[i - m_Count];

	m_Queue = temporary;
	m_Size = m_Size + other.m_Size;
	m_Count = count;

	return *this;
}

template<typename T>
bool Queue<T>::operator==(Queue& other)
{
	if (m_Count == other.m_Count && m_Size == other.m_Size)
	{
		for (size_t i = 0; i < m_Count; i++)
			if (m_Queue[i] != other.m_Queue[i])
				return 0;
		return 1;
	}
	return 0;
}

// add item to the queue
template<typename T>
void Queue<T>::push(T item)
{
	T* temporary;
	if (m_Count == m_Size)
	{
		temporary = new T[m_Size + 1];
		m_Size++;
	}
	else
		temporary = new T[m_Size];

	for (size_t i = 0; i < m_Count; i++)
		temporary[i] = m_Queue[i];
	temporary[m_Count] = item;
	m_Count++;

	m_Queue = temporary;
}

// pop item from queue
template<typename T>
T Queue<T>::pop()
{
	if (m_Size != 0)
	{
		T* temporary;
		m_Size--;
		if (m_Count != 0)
			m_Count--;
		temporary = new T[m_Size];

		for (size_t i = 0; i < m_Size; i++)
			temporary[i] = m_Queue[i + 1];

		T item = m_Queue[0];
		m_Queue = temporary;
		return item;
	}
	else
		throw;
}

// get count of items in queue
template<typename T>
int Queue<T>::getCount()
{
	return m_Size;
}

template<typename T>
bool Queue<T>::isEmpty()
{
	return m_Queue == 0;
}