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

    Queue& operator=(T* value); // default assignment operator
    Queue& operator=(Queue& value); // copy assignment operator
    Queue& operator=(Queue&& value); // move assignment operator
    Queue operator+(Queue& other);
    bool operator==(Queue& other);

    void push(T item); // add item to the queue
    T pop(); // pop item from queue
    int getCount(); // get count of items in queue
    bool isEmpty(); // is queue empty 

private:
    T* m_Queue; // {T, T, T, T, T, ...}
    int m_Size; // count of items in {T, T, T, T, T, ...}
};

template<typename T>
using queue = Queue<T>; // can initialize objects like queue<T> obj, as opposed to Queue<T> obj