#ifndef QUEUE_H 
#define QUEUE_H

#include "List.h"

template<typename T>
class Queue : List<T>
{
public:
    using List<T>::pushBack;
    using List<T>::popFront;
    /*friend std::ostream& operator<<(std::ostream& out, const Queue<T>& value)
    {
        out << "Queue(queue={";
        for (size_t i = 0; i < value.m_Size; i++)
        {
            out << value.m_Queue[i];
            if (i != value.m_Size - 1)
                out << ", ";
        }
        out << "}";
        out << ", count=" << value.m_Count << ", size=" << value.m_Size << ")";

        return out;
    }*/

    void push(T item) 
    { 
        pushBack(item); 
    };

    T pop() 
    {
        return popFront();
    };
};

template<typename T>
using queue = Queue<T>; // can initialize objects like queue<T> obj, as opposed to Queue<T> obj

#endif