#include <iostream>
#include "Queue.h"

// null constructor
template<typename T>
Queue<T>::Queue() : Queue(0)
{
	std::cout << __FUNCTION__ << std::endl;
}

// default constructor
template<typename T>
Queue<T>::Queue(int size)
{
	std::cout << __FUNCTION__ << std::endl;
	this->size = size;
	queue = new T[size];
}

// copy constructor
template<typename T>
Queue<T>::Queue(Queue& value)
{
	std::cout << __FUNCTION__ << std::endl;
}

// move constructor
template<typename T>
Queue<T>::Queue(Queue&& value)
{
	std::cout << __FUNCTION__ << std::endl;
}

// destructor
template<typename T>
Queue<T>::~Queue()
{
	std::cout << __FUNCTION__ << std::endl;
	delete queue;
}

// default assignment operator
template<typename T>
Queue<T>& Queue<T>::operator=(T* value)
{
	std::cout << __FUNCTION__ << std::endl;
}

// copy assignment operator
template<typename T>
Queue<T>& Queue<T>::operator=(Queue& value)
{
	std::cout << __FUNCTION__ << std::endl;
}

// move assignment operator
template<typename T>
Queue<T>& Queue<T>::operator=(Queue&& value)
{
	std::cout << __FUNCTION__ << std::endl;
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
	return size;
}

template<typename T>
bool Queue<T>::isEmpty()
{
	std::cout << __FUNCTION__ << std::endl;
}