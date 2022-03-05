#include <iostream>
#include "Queue.h"


int main()
{
    queue<int> myQueue;
    myQueue.push(2);

    queue<int> myQueue2(myQueue);

    std::cout << (myQueue == myQueue2) << std::endl;

    return 0;
}