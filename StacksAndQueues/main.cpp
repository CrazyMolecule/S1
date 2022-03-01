#include <iostream>
#include "Queue.h"
#include "Queue.hpp"

int main()
{
    queue<int> myQueue(4);
    std::cout << myQueue.getCount() << std::endl;
}