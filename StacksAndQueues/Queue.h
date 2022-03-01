#pragma once
template<typename T>
class Queue
{
public:
	Queue(); // нулевой конструктор
	Queue(T* queue); // обычный конструктор
	Queue(Queue& queue); // конструктор копирования
	Queue(Queue&& value); // конструктор перемещения
	void push(T item);
	T pop();
	int getCount();
	~Queue(); // деструктор

private:
	T* queue; // {T, T, T, T, T, ...}
	int count; // count of items in {T, T, T, T, T, ...}
};