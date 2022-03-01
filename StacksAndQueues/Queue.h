#pragma once
template<typename T>
class Queue
{
public:
	Queue(); // ������� �����������
	Queue(T* queue); // ������� �����������
	Queue(Queue& queue); // ����������� �����������
	Queue(Queue&& value); // ����������� �����������
	void push(T item);
	T pop();
	int getCount();
	~Queue(); // ����������

private:
	T* queue; // {T, T, T, T, T, ...}
	int count; // count of items in {T, T, T, T, T, ...}
};