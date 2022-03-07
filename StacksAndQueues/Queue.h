#ifndef QUEUE_H 
#define QUEUE_H

#include "List.h"

template<typename T>
class Queue : public List<T>
{
public:
    using List<T>::m_List;
    using List<T>::m_Size;
    using List<T>::m_Count;

    std::ostream& operator<<(std::ostream& out, const Queue<T>& value)
    {
        out << "Queue(queue={";
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
};

template<typename T>
using queue = Queue<T>;

template<typename T>
void Queue<T>::push(T item)
{
    T* temporary;
    if (m_Count == m_Size)
    {
        temporary = new T[m_Size + 1];
        m_Size++;
    }
    else
        temporary = new T[m_Size];

    for (size_t i = 0; i < m_Count; i++)
        temporary[i + 1] = m_List[i];
    temporary[0] = item;
    m_Count++;

    m_List = temporary;
}

template<typename T>
T Queue<T>::pop()
{
    if (m_Size != 0)
    {
        T* temporary;
        T item = m_List[m_Size];

        m_Size--;
        if (m_Count != 0)
            m_Count--;
        temporary = new T[m_Size];

        for (size_t i = 0; i < m_Size; i++)
            temporary[i] = m_List[i];

        m_List = temporary;
        return item;
    }
    else
        throw;
}

#endif