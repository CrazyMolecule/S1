#include <iostream>

template<typename T>
class Queue
{
private:
	T* m_Queue; // {T, T, T, T, T, ...}
	int m_Size; // count of spaces in {T, T, T, T, T, ...}
	int m_Count; // count of items in {T, T, T, T, T, ...}

	void replaceQueue(Queue& value);

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
};

template<typename T>
using queue = Queue<T>; // can initialize objects like queue<T> obj, as opposed to Queue<T> obj

// null constructor
template<typename T>
Queue<T>::Queue() : Queue(0) {}

// default constructor
template<typename T>
Queue<T>::Queue(int size) : m_Size(size), m_Queue(new T[size]), m_Count(0) {}

// copy constructor
template<typename T>
Queue<T>::Queue(Queue& value) : m_Size(value.m_Size), m_Count(value.m_Count)
{
	replaceQueue(value);
}

// move constructor
template<typename T>
Queue<T>::Queue(Queue&& value) : m_Size(value.m_Size), m_Queue(value.m_Queue), m_Count(value.m_Count)
{
	value.m_Queue = NULL;
	value.m_Size = NULL;
	value.m_Count = NULL;
}

// destructor
template<typename T>
Queue<T>::~Queue()
{
	delete[] m_Queue;
}

// copy assignment operator
template<typename T>
Queue<T>& Queue<T>::operator=(Queue& value)
{
	replaceQueue(value);

	m_Size = value.m_Size;
	m_Count = value.m_Count;

	return *this;
}

// move assignment operator
template<typename T>
Queue<T>& Queue<T>::operator=(Queue&& value)
{
	m_Size = value.m_Size;
	m_Queue = value.m_Queue;
	m_Count = value.m_Count;

	value.m_Queue = NULL;
	value.m_Size = NULL;
	value.m_Count = NULL;
	return *this;
}

template<typename T>
Queue<T> Queue<T>::operator+(Queue& other) /// (!!!!)
{
	int count = m_Count + other.m_Count;
	int size = m_Size + other.m_Size;
	Queue<T> tempQueue(size);

	for (size_t i = 0; i < m_Count; i++)
		tempQueue.m_Queue[i] = m_Queue[i];
	for (size_t i = m_Count; i < count; i++)
		tempQueue.m_Queue[i] = other.m_Queue[i - m_Count];

	tempQueue.m_Count = count;

	return tempQueue;
}

template<typename T>
bool Queue<T>::operator==(Queue& other)
{
	if (m_Count == other.m_Count && m_Size == other.m_Size)
	{
		for (size_t i = 0; i < m_Count; i++)
			if (m_Queue[i] != other.m_Queue[i])
				return 0;
		return 1;
	}
	return 0;
}

// add item to the queue
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
		temporary[i + 1] = m_Queue[i];
	temporary[0] = item;
	m_Count++;

	m_Queue = temporary;
}

// pop item from queue
template<typename T>
T Queue<T>::pop()
{
	if (m_Size != 0)
	{
		T* temporary;
		T item = m_Queue[m_Size];

		m_Size--;
		if (m_Count != 0)
			m_Count--;
		temporary = new T[m_Size];

		for (size_t i = 0; i < m_Size; i++)
			temporary[i] = m_Queue[i];


		m_Queue = temporary;
		return item;
	}
	else
		throw;
}

// get count of items in queue
template<typename T>
int Queue<T>::getCount()
{
	return m_Size;
}

template<typename T>
bool Queue<T>::isEmpty()
{
	return m_Queue == 0;
}

template<typename T>
void Queue<T>::replaceQueue(Queue& value)
{
	delete[] m_Queue;
	m_Queue = nullptr;

	m_Queue = new T[value.m_Size];
	for (size_t i = 0; i < m_Count; i++)
		m_Queue[i] = value.m_Queue[i];
}

template <typename T>
class Stack 
{
private:
	T* m_Stack;
	T m_Top;
	int m_Count;
	int m_Size;

public:
	//Methods
	Stack();					// Null constructor
	Stack(int size);			// Default constructor
	void push(T element);		// Push to top
	T pop();					// Removes top element
	T returnValue(int elementNo);
	T peek();					// Peek at top element
	int getCount();			// Returns amount of elements in stack
	~Stack();
};

template <typename T>
Stack<T>::Stack() : Stack(0) {}

template <typename T>
Stack<T>::Stack(int size) : m_Stack(new T[size]), m_Count(0), m_Size(size), m_Top(0) {}

template <typename T>
void Stack<T>::push(T element) 
{

	T* tempStack;
	if (m_Count == m_Size)
	{
		tempStack = new T[m_Size + 1];
		m_Size++;
	}
	else
		tempStack = new T[m_Size];

	for (int i = 0; i < m_Count; i++)
		tempStack[i] = m_Stack[i];
	tempStack[m_Count] = element;
	m_Count++;
	m_Stack = tempStack;
	m_Top = m_Stack[m_Count - 1];
}

template <typename T>
T Stack<T>::pop() 
{
	T* tempStack;

	tempStack = new T[m_Size];
	m_Count--;
	m_Top = m_Stack[m_Count];
	for (int i = 0; i < m_Count; i++)
		tempStack[i] = m_Stack[i];

	m_Stack = tempStack;
	return m_Top;
}

template <typename T>
T Stack<T>::returnValue(int elementNo) 
{

	return m_Stack[elementNo];

}

template <typename T>
T Stack<T>::peek() 
{
	return m_Stack[m_Count - 1];
}

template <typename T>
int Stack<T>::getCount() 
{
	return m_Count;
}

template <typename T>
Stack<T>::~Stack() 
{
	delete[] m_Stack;
}

template <typename T>
using stack = Stack<T>; // can initialize objects like queue<T> obj, as opposed to Queue<T> obj

int main()
{
	stack<int> myQueue;
	myQueue.push(5);
	myQueue.push(4);

	stack<int> myQueue2;
	myQueue2.push(3);
	myQueue2.push(3);

	// stack<int> myQueue3 = myQueue + myQueue2;
}