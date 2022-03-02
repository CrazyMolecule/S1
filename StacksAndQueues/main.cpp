#include <iostream>
#include "Queue.h"
#include "Queue.hpp"

#include <vector>;


int main()
{
    queue<int> myQueue(1); // null constr test
    myQueue.push(5);
    queue<int> myQueue2(5); // default constr test

    //myQueue = myQueue + myQueue2;
    std::cout << myQueue << std::endl;
}