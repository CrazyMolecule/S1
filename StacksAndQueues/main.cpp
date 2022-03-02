#include <iostream>
#include "Stack.h"

int main()
{
	Stack<int> myStack;
	return 0; // returns 0

    stack<int> myStack; // null constr test

    stack<int> myStack2(5); // default constr test

    stack<int> myStack3(myStack2); // copy constr test

    std::cout << myStack3.getCount() << std::endl; // getCount test

    std::vector<stack<char*>> v; // !!! #include <vector>;
    v.push_back(stack<char*>(25)); // move constr test

    myStack = myStack2; // copy assignment operator test
}