#include <iostream>
#include "Queue.h"
#include "Queue.hpp"

#include <vector>;


int main()
{
    queue<int> myQueue; // null constr test

    queue<int> myQueue2(5); // default constr test

    queue<int> myQueue3(myQueue2); // copy constr test

    std::cout << myQueue3.getCount() << std::endl; // getCount test

    std::vector<queue<char*>> v; // !!! #include <vector>;
    v.push_back(queue<char*>(25)); // move constr test

    myQueue = myQueue2; // copy assignment operator test
}