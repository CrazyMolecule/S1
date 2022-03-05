#pragma once

#include <string>

class Element
{
private:
	enum Type
	{
		digit,
		closeParenthesis,
		openParenthesis,
		operators
	};

	std::string m_Value = "";
	Type m_Type;

    // METHODS - Check Type
    int getOperatorId();
    bool isDigit();
    bool isOpenParenthesis();
    bool isCloseParenthesis();
    bool isOperators(); // is +/-/%/* or /

public:
    Element(std::string value);
};
using element = Element;