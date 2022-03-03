#include <iostream>
#include "Queue.h"
#include "Queue.hpp"

#include <vector>;


int main()
{
    queue<int> myQueue;
    myQueue.push(5);
    myQueue.push(5);
    std::cout << myQueue << std::endl;

    queue<int> myQueue2;
    myQueue2.push(3);
    myQueue2.push(3);
    std::cout << myQueue2 << std::endl;

    queue<int> myQueue3(myQueue + myQueue2);

    std::cout << myQueue3 << std::endl;
}