#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>

class Element
{
public:
	enum Type
	{
		digit,
		closeParenthesis,
		openParenthesis,
		operators
	};

private:
	std::string m_Value = "";
	Type m_Type;

    // METHODS - Check Type
    bool isDigit();
    bool isOpenParenthesis();
    bool isCloseParenthesis();
    bool isOperators(); // is +/-/%/* or /

public:
    Element(std::string value);
	Element(char value);

	int getOperatorId();
	Type getType();
	std::string getElement();

	long long calculate(long long a, long long b);

	explicit operator long long() const;

};
using element = Element;

#endif