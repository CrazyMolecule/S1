#include "Converter.h"

void Converter::setInfixQueue(std::string line)
{
	m_InfixQueue = splitAndTransform(line);
}

queue<element> Converter::splitAndTransform(std::string line, char sep = ' ')
{
	/*
	* Split string
	*/
	return;
}

Converter::Converter(std::string& inputLine)
{
	setInfixQueue(inputLine); // fills in m_Infix field
}

Converter& Converter::toPostfix()
{
	if (!m_InfixQueue.isEmpty())
	{
		/*
		* Convert from InfixQueue to PostfixQueue using m_Stack
		*/
		return;
	}
}

long long Converter::calculate()
{
	if (!m_PostfixQueue.isEmpty())
	{
		/*
		* Calc PostfixQueue to long long
		*/
		return;
	}
}