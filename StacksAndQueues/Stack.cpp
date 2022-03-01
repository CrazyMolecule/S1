#include "Stack.h"


// null constructor
template<typename T>
Stack<T>::Stack()
{
}

// default constructor
template<typename T>
Stack<T>::Stack(T* myStack)
{
}

// copy constructor
template<typename T>
Stack<T>::Stack(Stack& myStack)
{
}

// move constructor
template<typename T>
Stack<T>::Stack(Stack&& value)
{
}

// destructor
template<typename T>
Stack<T>::~Stack()
{
}

// default assignment operator
template<typename T>
Stack<T>& Stack<T>::operator=(T* myStack)
{
}

// copy assignment operator
template<typename T>
Stack<T>& Stack<T>::operator=(Stack& myStack)
{
}

// move assignment operator
template<typename T>
Stack<T>& Stack<T>::operator=(Stack&& value)
{
}

// add item to the queue
template<typename T>
void Stack<T>::push(T item)
{
}

// pop item from queue
template<typename T>
T Stack<T>::pop()
{
}

// get count of items in queue
template<typename T>
int Stack<T>::getCount()
{
}