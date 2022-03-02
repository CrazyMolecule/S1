#pragma once
template<typename T>
#define MAX 100 //max size for stack
class Stack
{
public:

	Stack(); // Null constructor
	Stack(T* myStack); // Standard constructor
	Stack(Stack& myStack); // copy constructor
	Stack(Stack&& value); // move constructor
	~Stack(); //Destructor
	
	Stack& operator=(T* myStack); // default assignment operator
	Stack& operator=(Stack& myStack); // copy assignment operator
	Stack& operator=(Stack&& value); // move assignment operator

	void push(T item); // add item to stack
	T pop(); //remove last item added from stack
	int getCount(); //get count of items in stack
	T getTop();
	
private:
	T myStack[]; // {bottom <<<<< 1, 2, 3, 4, 5, 6... >>>>>> top}
	int count; //count of items in stack
	int _size;
	int _count;
	T _top;
};



//////////////////////////////////////////////////////////////////////////////




// null constructor
template <typename T>
Stack<T>::Stack()
{
}

// default constructor
template <typename T>
Stack<T>::Stack(T* myStack)
{
	new 
}

// copy constructor
template <typename T>
Stack<T>::Stack(Stack& myStack)
{
}

// move constructor
template <typename T>
Stack<T>::Stack(Stack&& value)
{
}

// destructor
template <typename T>
Stack<T>::~Stack()
{
}

// default assignment operator
template <typename T>
Stack<T>& Stack<T>::operator=(T* myStack)
{
}

// copy assignment operator
template <typename T>
Stack<T>& Stack<T>::operator=(Stack& myStack)
{
}

// move assignment operator
template <typename T>
Stack<T>& Stack<T>::operator=(Stack&& value)
{
}

// add item to the queue
template <typename T>
void Stack<T>::push(T item)
{
}

// pop item from queue
template <typename T>
T Stack<T>::pop()
{
}

// get count of items in queue
template <typename T>
int Stack<T>::getCount()
{
}