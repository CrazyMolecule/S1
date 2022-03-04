#pragma once

template <typename T>
class Stack
{
private:
	T* m_Stack;
	T m_Top;
	int m_Count;
	int m_Size;

public:
	//Methods
	Stack();					// Null constructor
	Stack(int size);			// Default constructor
	void push(T element);		// Push to top
	T pop();					// Removes top element
	T returnValue(int elementNo);
	T peek();					// Peek at top element
	int getCount();			// Returns amount of elements in stack
	~Stack();
};

template <typename T>
Stack<T>::Stack() : Stack(0) {}

template <typename T>
Stack<T>::Stack(int size) : m_Stack(new T[size]), m_Count(0), m_Size(size), m_Top(0) {}

template <typename T>
void Stack<T>::push(T element)
{

	T* tempStack;
	if (m_Count == m_Size)
	{
		tempStack = new T[m_Size + 1];
		m_Size++;
	}
	else
		tempStack = new T[m_Size];

	for (int i = 0; i < m_Count; i++)
		tempStack[i] = m_Stack[i];
	tempStack[m_Count] = element;
	m_Count++;
	m_Stack = tempStack;
	m_Top = m_Stack[m_Count - 1];
}

template <typename T>
T Stack<T>::pop()
{
	T* tempStack;

	tempStack = new T[m_Size];
	m_Count--;
	m_Top = m_Stack[m_Count];
	for (int i = 0; i < m_Count; i++)
		tempStack[i] = m_Stack[i];

	m_Stack = tempStack;
	return m_Top;
}

template <typename T>
T Stack<T>::returnValue(int elementNo)
{

	return m_Stack[elementNo];

}

template <typename T>
T Stack<T>::peek()
{
	return m_Stack[m_Count - 1];
}

template <typename T>
int Stack<T>::getCount()
{
	return m_Count;
}

template <typename T>
Stack<T>::~Stack()
{
	delete[] m_Stack;
}

template <typename T>
using stack = Stack<T>; // can initialize objects like queue<T> obj, as opposed to Queue<T> obj