#include "Converter.h"

void Converter::setInfixQueue(std::string line)
{
	m_Infix = splitAndTransform(line);
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
	if (!m_Infix.isEmpty())
	{
		/*
		* Convert from m_Infix to m_Postfix using m_Buffer
		*/
		return;
	}
}

long long Converter::calculate()
{
	if (!m_Postfix.isEmpty())
	{
		/*
		* Calc m_Postfix to long long
		*/
		return;
	}
}