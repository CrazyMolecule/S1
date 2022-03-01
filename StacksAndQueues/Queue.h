#pragma once
template<typename T>
class Queue
{
public:
	Queue(); // null constructor
	Queue(T* queue); // default constructor
	Queue(Queue& queue); // copy constructor
	Queue(Queue&& value); // move constructor
	~Queue(); // destructor
	
	Queue& operator=(T* queue); // default assignment operator
	Queue& operator=(Queue& queue); // copy assignment operator
	Queue& operator=(Queue&& value); // move assignment operator
	
	void push(T item); // add item to the queue
	T pop(); // pop item from queue
	int getCount(); // get count of items in queue
	
private:
	T* queue; // {T, T, T, T, T, ...}
	int count; // count of items in {T, T, T, T, T, ...}
};