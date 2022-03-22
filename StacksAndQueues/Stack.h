#pragma once

#include "List.h"

namespace bavykin
{
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
		if (m_Size != 0)
		{
			T* temporary;
			T item = m_List[m_Count - 1];

			m_Size--;
			if (m_Count != 0)
				m_Count--;
			temporary = new T[m_Size];

			for (size_t i = 0; i < m_Size; i++)
				temporary[i] = m_List[i];

			m_List = temporary;
			return item;
		}
	}

	template <typename T>
	T Stack<T>::peek()
	{
		return m_List[m_Count - 1];
	}

	template <typename T>
	using stack = Stack<T>;
}