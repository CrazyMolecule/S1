#include "Converter.h"


void Converter::setInfixQueue(std::string line)
{
	m_InfixQueue = splitAndTransform(line);
}

// "( 5 + 15 ) / ( 4 + 7 – 1 )" -> Queue{}
queue<element> Converter::splitAndTransform(std::string line, const char sep)
{
	queue<element> tempQueue;

	std::string temp = "";
	int i = 0;

	while (i < line.size())
	{
		temp = "";

		if (line[i] == ' ')
		{
			i++;
			continue;
		}
		else if (!std::isdigit(line[i]))
		{
			temp = line[i];
			i++;
		}
		else
		{
			while (std::isdigit(line[i]))
			{
				temp += line[i];
				i++;
			}
		}

		element now = element(temp);
		tempQueue.push(now);
	}

	return tempQueue;
}

Converter::Converter(std::string& Line)
{
	setInfixQueue(Line); // fills in m_Infix field
}

Converter& Converter::toPostfix()
{
	using type = element::Type;

	std::cout << "НАЧАЛО \n{" << std::endl;
	std::cout << "m_InfixQueue: " << m_InfixQueue << std::endl;
	std::cout << "m_PostfixQueue: " << m_PostfixQueue << std::endl;
	std::cout << "m_Stack: " << m_Stack << std::endl;
	std::cout << "}" << std::endl;

	while (!m_InfixQueue.isEmpty())
	{
		element now = m_InfixQueue.pop();
		switch (now.getType())
		{
		case type::openParenthesis:
			m_Stack.push(now);
			std::cout << "openParenthesis \n{" << std::endl;
			std::cout << "(now " << now << ")" << std::endl;
			std::cout << "m_InfixQueue: " << m_InfixQueue << std::endl;
			std::cout << "m_PostfixQueue: " << m_PostfixQueue << std::endl;
			std::cout << "m_Stack: " << m_Stack << std::endl;
			std::cout << "}" << std::endl;
			break;
		case type::digit:
			m_PostfixQueue.push(now);
			std::cout << "digit \n{" << std::endl;
			std::cout << "(now " << now << ")" << std::endl;
			std::cout << "m_InfixQueue: " << m_InfixQueue << std::endl;
			std::cout << "m_PostfixQueue: " << m_PostfixQueue << std::endl;
			std::cout << "m_Stack: " << m_Stack << std::endl;
			std::cout << "}" << std::endl;
			break;
		case type::closeParenthesis:
			now = m_Stack.pop();
			while (now.getType() != type::openParenthesis)
			{
				m_PostfixQueue.push(now);
				if (m_Stack.getCount() == 0)
				{
					throw "Error: Check the quantity of brackets!";
				}

				std::cout << "m_Stack RIGHT NOWWWW: " << m_Stack << std::endl;
				now = m_Stack.pop();
				
			}
			std::cout << "closeParenthesis \n{" << std::endl;
			std::cout << "(now " << now << ")" << std::endl;
			std::cout << "m_InfixQueue: " << m_InfixQueue << std::endl;
			std::cout << "m_PostfixQueue: " << m_PostfixQueue << std::endl;
			std::cout << "m_Stack: " << m_Stack << std::endl;
			std::cout << "}" << std::endl;
			break;
		case type::operators:
			if (m_Stack.isEmpty())
			{
				m_Stack.push(now);
			}
			else if (now.getOperatorId() <= m_Stack.peek().getOperatorId())
			{
				while (m_Stack.peek().getOperatorId() > -1)
				{
					m_PostfixQueue.push(m_Stack.pop());
					m_Stack.push(now);
					if (m_Stack.isEmpty()) // Выход из цикла заранее, чтобы не крашилось - m_Stack.peek() returns 0
						break;
				}
			}
			else
			{
				m_Stack.push(now);
			}

			std::cout << "operators \n{" << std::endl;
			std::cout << "(now " << now << ")" << std::endl;
			std::cout << "m_InfixQueue: " << m_InfixQueue << std::endl;
			std::cout << "m_PostfixQueue: " << m_PostfixQueue << std::endl;
			std::cout << "m_Stack: " << m_Stack << std::endl;
			std::cout << "}" << std::endl;
			break;
		}

		if (m_InfixQueue.isEmpty()) // Выталкивание под конец
		{
			while (!m_Stack.isEmpty())
			{
				m_PostfixQueue.push(m_Stack.pop());
			}
		}
		std::cout << "[!!!] Прошла итерация " << std::endl;
	}

	std::cout << "Вот чо получилось: " << m_PostfixQueue << std::endl;

	return *this;
}

long long Converter::calculate()
{
	if (!m_PostfixQueue.isEmpty())
	{
		using type = element::Type;

		stack<long long> out;

		m_PostfixQueue.reverse(); // FIXIT: Вызвано исключение по адресу 0x5F1434B0 (vcruntime140.dll) в StacksAndQueues.exe: 0xC0000005: нарушение прав доступа при чтении по адресу 0x82763A0C.

		while (!m_PostfixQueue.isEmpty())
		{
			auto now = m_PostfixQueue.pop();

			if (now.getType() == type::digit)
			{
				long long nowDigit = static_cast<long long>(now);

				out.push(nowDigit);
			}
			else if (now.getType() == type::operators)
			{
				long long b = out.pop();
				long long a = out.pop();

				if (now.getElement()[0] == '%')
				{
					out.push(((a % b) + b) % b);
				}
				else
				{
					out.push(now.calculate(a, b));
				}
			}
		}

		return out[0]; // тут я хз, надо последний или первый
	}
}