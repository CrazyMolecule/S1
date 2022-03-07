
#ifndef STACK_H 
#define STACK_H

template <typename T>
class Stack : public List<T>
{
private:
	
	T m_Top;

public:
	//Methods
	
	void push(T);		// Push to top
	T pop();					// Removes top element
	T peek();					// Peek at top element
};


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
T Stack<T>::peek()
{
	return m_Stack[m_Count - 1];
}


template <typename T>
using stack = Stack<T>; // can initialize objects like queue<T> obj, as opposed to Queue<T> obj

#endif