#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>
#include <iostream>

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
	std::string m_Value;
	Type m_Type;

	// METHODS - Check Type
	
	bool isOpenParenthesis();
	bool isCloseParenthesis();
	bool isOperators(); // is +/-/%/* or /

public:
	Element();
	Element(std::string);
	Element(char);
	Element(const Element&);
	//Element(Element&&);

	int getOperatorId();
	Type getType();
	std::string getElement();
	bool isDigit();

	long long calculate(long long, long long);

	explicit operator long long() const;
	Element& operator=(const Element&);

	friend std::ostream& operator<<(std::ostream& out, const Element& value)
	{
		out << value.m_Value;

		return out;
	};

};
using element = Element;

#endif