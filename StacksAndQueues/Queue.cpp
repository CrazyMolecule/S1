#include "Queue.h"

// null constructor
template<typename T>
Queue<T>::Queue()
{
}

// default constructor
template<typename T>
Queue<T>::Queue(T* queue)
{
}

// copy constructor
template<typename T>
Queue<T>::Queue(Queue& queue)
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
Queue<T>& Queue<T>::operator=(T* queue)
{
}

// copy assignment operator
template<typename T>
Queue<T>& Queue<T>::operator=(Queue& queue)
{
}

// move assignment operator
template<typename T>
Queue<T>& Queue<T>::operator=(Queue&& value)
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

