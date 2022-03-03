#pragma once

template<typename T>
class Queue
{
public:
    Queue(); // null constructor
    Queue(int size); // default constructor
    Queue(Queue& value); // copy constructor
    Queue(Queue&& value); // move constructor
    ~Queue(); // destructor

    Queue& operator=(Queue& value); // copy assignment operator
    Queue& operator=(Queue&& value); // move assignment operator
    Queue operator+(Queue& other);
    bool operator==(Queue& other);
    friend std::ostream& operator<<(std::ostream& out, const Queue<T>& value)
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
    }

    void push(T item); // add item to the queue
    T pop(); // pop item from queue
    int getCount(); // get count of items in queue
    bool isEmpty(); // is queue empty (m_Count == 0)

private:
    T* m_Queue; // {T, T, T, T, T, ...}
    int m_Size; // count of spaces in {T, T, T, T, T, ...}
    int m_Count; // count of items in {T, T, T, T, T, ...}

    void replaceQueue(Queue& value);
};

template<typename T>
using queue = Queue<T>; // can initialize objects like queue<T> obj, as opposed to Queue<T> obj