#pragma once

#include <string>

#include "Queue.h"
#include "Stack.h"
#include "Element.h"

class Converter
{
private:
	queue<element> m_Infix;
	stack<element> m_Buffer;
	queue<element> m_Postfix;

	void setInfixQueue(std::string line);

    // METHODS - toInfixQueue
	queue<element> splitAndTransform(std::string line, char sep = ' ');
public:
	Converter(std::string& inputLine);

	Converter& toPostfix();
	long long calculate();
};
