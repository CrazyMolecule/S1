#ifndef CONVERTER_H 
#define CONVERTER_H

#include <string>

#include "Queue.h"
#include "Stack.h"
#include "Element.h"

class Converter
{
private:
	queue<element> m_InfixQueue;
	stack<element> m_Stack;
	queue<element> m_PostfixQueue;

	void setInfixQueue(std::string line);

    // METHODS - toInfixQueue
	queue<element> splitAndTransform(std::string line, char sep = ' ');
public:
	Converter(std::string& inputLine);

	Converter& toPostfix();
	long long calculate();
};

#endif
