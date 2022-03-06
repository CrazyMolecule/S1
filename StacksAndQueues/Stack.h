
#ifndef STACK_H 
#define STACK_H

template <typename T>
class Stack : public List<T>
{
private:
	
	using List<T>::m_List;
	using List<T>::m_Size;
	using List<T>::m_Count;
	T m_Top;


public:
	//Methods

	void push(T element);		// Push to top
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
		tempStack[i] = m_List[i];
	tempStack[m_Count] = element;
	m_Count++;
	m_List = tempStack;
	m_Top = m_List[m_Count - 1];
}

template <typename T>
T Stack<T>::pop()
{
	T* tempStack;

	tempStack = new T[m_Size];
	m_Count--;
	m_Top = m_List[m_Count];
	for (int i = 0; i < m_Count; i++)
		tempStack[i] = m_List[i];

	m_List = tempStack;
	return m_Top;
}


template <typename T>
T Stack<T>::peek()
{
	return m_List[m_Count - 1];
}


template <typename T>
using stack = Stack<T>; // can initialize objects like queue<T> obj, as opposed to Queue<T> obj

#endif