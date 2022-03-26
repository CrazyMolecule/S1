#pragma once

#include <string>
#include <iostream>

namespace bavykin
{
	class Element
	{
	public:
		enum class Type
		{
			digit,
			closeParenthesis,
			openParenthesis,
			operators
		};

	private:
		std::string m_Value;
		Type m_Type;

		bool isOpenParenthesis();
		bool isCloseParenthesis();
		bool isOperators();

	public:
		Element() noexcept;
		Element(std::string);
		Element(char);
		Element(const Element&) noexcept;

		bool isDigit();
		int getOperatorId();
		Type getType() noexcept;
		std::string getElement() noexcept;

		long long calculate(long long, long long);

		explicit operator long long() const;
		Element& operator=(const Element&) noexcept;

		friend std::ostream& operator<<(std::ostream& out, const Element& value)
		{
			out << value.m_Value;

			return out;
		};

	};
	using element = Element;
}