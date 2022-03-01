#include "Queue.h"

// null constructor
template<typename T>
Queue<T>::Queue()
{
}

// default constructor
template<typename T>
Queue<T>::Queue(T* value)
{
}

// copy constructor
template<typename T>
Queue<T>::Queue(Queue& value)
{
}

// move constructor
template<typename T>
Queue<T>::Queue(Queue&& value)
{
}

// destructor
template<typename T>
Queue<T>::~Queue()
{
}

// default assignment operator
template<typename T>
Queue<T>& Queue<T>::operator=(T* value)
{
}

// copy assignment operator
template<typename T>
Queue<T>& Queue<T>::operator=(Queue& value)
{
}

// move assignment operator
template<typename T>
Queue<T>& Queue<T>::operator=(Queue&& value)
{
}

template<typename T>
Queue<T> Queue<T>::operator+(Queue& other)
{
}

template<typename T>
bool Queue<T>::operator==(const Queue& other)
{
}

// add item to the queue
template<typename T>
void Queue<T>::push(T item)
{
}

// pop item from queue
template<typename T>
T Queue<T>::pop()
{
}

// get count of items in queue
template<typename T>
int Queue<T>::getCount()
{
}

