#ifndef CONVERTER_H 
#define CONVERTER_H

#include <string>
#include <iostream>

#include "Queue.h"
#include "Stack.h"
#include "Element.h"

class Converter
{
private:
	queue<element> m_InfixQueue;
	stack<element> m_Stack;
	queue<element> m_PostfixQueue;

	void setInfixQueue(std::string);

    // METHODS - toInfixQueue
	queue<element> splitAndTransform(std::string, const char = ' ');
public:
	Converter(std::string&);

	Converter& toPostfix();
	long long calculate();
};

#endif
