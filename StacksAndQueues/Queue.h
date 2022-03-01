#pragma once
template<typename T>
class Queue
{
public:
	Queue();
	Queue(T* queue);
	Queue(Queue& queue);
	Queue(Queue&& value);
	void push(T item);
	T pop();
	int getCount();
	~Queue();

private:
	T* queue;
	int count;
};