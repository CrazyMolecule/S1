#include "List.h"
#include <memory>

#ifndef STACK_H
#define STACK_H
namespace bavykin
{
	template<typename T>
	class Stack : public List<T>
	{
	private:
		using List<T>::m_List;
		using List<T>::m_Size;
		using List<T>::m_Count;

	public:
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

		void push(T) noexcept;
		T pop();
		T peek();
	};

	template <typename T>
	void Stack<T>::push(T item) noexcept
	{
		std::shared_ptr<T[]> temporary;
		if (m_Count == m_Size)
		{
			temporary = std::shared_ptr<T[]>(new T[m_Size + 1]);
			m_Size++;
		}
		else
		{
			temporary = std::shared_ptr<T[]>(new T[m_Size]);
		}

		for (size_t i = 0; i < m_Count; i++)
		{
			temporary[i] = m_List[i];
		}
		temporary[m_Count] = item;
		m_Count++;

		m_List = std::move(temporary);
	}

	template <typename T>
	T Stack<T>::pop()
	{
		if (m_Size == 0)
		{
			throw std::logic_error("The stack is empty!");
		}

		std::shared_ptr<T[]> temporary;
		T item = m_List[m_Count - 1];

		m_Size--;
		if (m_Count != 0)
		{
			m_Count--;
		}
		temporary = std::shared_ptr<T[]>(new T[m_Size]);

		for (size_t i = 0; i < m_Size; i++)
		{
			temporary[i] = m_List[i];
		}

		m_List = std::move(temporary);
		return item;
	}

	template <typename T>
	T Stack<T>::peek()
	{
		return m_List[m_Count - 1];
	}

	template <typename T>
	using stack = Stack<T>;
}
#endif