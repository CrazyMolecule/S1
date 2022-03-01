#pragma once
template<typename T>
class Queue
{
public:
	Queue(); // null constructor
	Queue(T* queue); // default constructor
	Queue(Queue& queue); // copy constructor
	Queue(Queue&& value); // move constructor
	void push(T item);
	T pop();
	int getCount();
	~Queue(); // destructor

private:
	T* queue; // {T, T, T, T, T, ...}
	int count; // count of items in {T, T, T, T, T, ...}
};