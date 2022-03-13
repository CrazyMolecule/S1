#ifndef STACK_H 
#define STACK_H

template <typename T>
class Stack : public List<T>
{
public:
	using List<T>::m_List;
	using List<T>::m_Size;
	using List<T>::m_Count;
	using List<T>::List;

	friend std::ostream& operator<<(std::ostream& out, const Stack<T>& value)
	{
		out << "Stack(stack={";
		for (size_t i = 0; i < value.m_Size; i++)
		{
			out << value.m_List[i];
			if (i != value.m_Size - 1)
				out << ", ";
		}
		out << "}";
		out << ", count=" << value.m_Count << ", size=" << value.m_Size << ")";

		return out;
	};

	void push(T);
	T pop();
	T peek();
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
	
}

template <typename T>
T Stack<T>::pop()
{

	T* tempStack = new T[m_Size];
	T peekedValue = peek();
	m_Count--;
	for (int i = 0; i < m_Count; i++)
		tempStack[i] = m_List[i];

	m_List = tempStack;
	delete[] tempStack;
	return peekedValue;
}


template <typename T>
T Stack<T>::peek()
{
	return m_List[0];
}


template <typename T>
using stack = Stack<T>; // can initialize objects like queue<T> obj, as opposed to Queue<T> obj

#endif