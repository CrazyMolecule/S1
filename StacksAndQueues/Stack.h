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
	
private:
	T* myStack[MAX]; // {bottom <<<<< 1, 2, 3, 4, 5, 6... >>>>>> top}
	int count; //count of items in stack
};

