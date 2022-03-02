#include <iostream>

#include "Queue.h"

// null constructor
template<typename T>
Queue<T>::Queue() : Queue(0)
{
	std::cout << __FUNCTION__ << "()" << std::endl;
}

// default constructor
template<typename T>
Queue<T>::Queue(int size) : m_Size(size), m_Queue(new T[size]), m_Count(0)
{
	std::cout << __FUNCTION__ << "(int size)" << std::endl;
}

// copy constructor
template<typename T>
Queue<T>::Queue(Queue& value) : m_Size(value.m_Size), m_Queue(value.m_Queue), m_Count(value.m_Count)
{
	std::cout << __FUNCTION__ << "(Queue& valueû)" << std::endl;
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
	std::cout << __FUNCTION__ << std::endl;
	// delete[] m_Queue;
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
	m_Size = value.m_Size;
	m_Queue = value.m_Queue;
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
	std::cout << __FUNCTION__ << std::endl;
}

template<typename T>
bool Queue<T>::operator==(Queue& other)
{
	std::cout << __FUNCTION__ << std::endl;
}



// add item to the queue
template<typename T>
void Queue<T>::push(T item)
{
	std::cout << __FUNCTION__ << std::endl;
	T* temporary;
	if (m_Count == m_Size)
		T* temporary = new T[m_Size + 1];
	else
		T* temporary = new T[m_Size];

	for (size_t i = 0; i < m_Count; i++)
		temporary[i] = m_Count[i];
	temporary[m_Count + 1] = item;

	m_Queue = temporary;
}

// pop item from queue
template<typename T>
T Queue<T>::pop()
{
	std::cout << __FUNCTION__ << std::endl;
}

// get count of items in queue
template<typename T>
int Queue<T>::getCount()
{
	std::cout << __FUNCTION__ << std::endl;
	return m_Size;
}

template<typename T>
bool Queue<T>::isEmpty()
{
	std::cout << __FUNCTION__ << std::endl;
}