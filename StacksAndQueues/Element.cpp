#include "Element.h"

namespace bavykin
{
    Element::Element()
    {
        m_Value = "";
        m_Type = Type::digit;
    }

    Element::Element(std::string value)
    {
        m_Value = value;

        if (isDigit())
        {
            m_Type = Type::digit;
        }
        else if (isOpenParenthesis())
        {
            m_Type = Type::openParenthesis;
        }
        else if (isCloseParenthesis())
        {
            m_Type = Type::closeParenthesis;
        }
        else if (isOperators())
        {
            m_Type = Type::operators;
        }
    }

    Element::Element(char value)
    {
        char* arr = new char[1];
        arr[0] = value;
        Element n(arr);
    }

    Element::Element(const Element& value)
    {
        m_Value = value.m_Value;
        m_Type = value.m_Type;
    }

    bool Element::isDigit()
    {
        for (char c : m_Value)
        {
            if (!std::isdigit(c))
            {
                return false;
            }
        }
        return true;
    }

    bool Element::isOpenParenthesis()
    {
        return '(' == m_Value[0];
    }

    bool Element::isCloseParenthesis()
    {
        return ')' == m_Value[0];
    }

    bool Element::isOperators()
    {
        return getOperatorId() != -1;
    }

    int Element::getOperatorId()
    {
        switch (m_Value[0])
        {
        case '*':
        case '/':
        case '%':
            return 1;
        case '+':
        case '-':
            return 0;
        }
        return -1;
    }

    Element::Type Element::getType()
    {
        return m_Type;
    }

    std::string Element::getElement()
    {
        return m_Value;
    }

    long long Element::calculate(long long a, long long b)
    {
        long long c = 0;

        switch (m_Value[0])
        {
        case '+':
            c = a + b;
            break;
        case '-':
            c = a - b;
            break;
        case '*':
            c = a * b;
            break;
        case '/':
            c = a / b;
            break;
        case '%':
            c = a % b;
            break;
        }

        return c;
    }

    Element::operator long long() const
    {
        if (m_Type != Type::digit)
            throw "Not correct transform";

        long long out = 0;

        for (char c : m_Value)
        {
            out = out * 10 + (c - '0');
        }           

        return out;
    }

    Element& Element::operator=(const Element& value)
    {
        m_Value = value.m_Value;
        m_Type = value.m_Type;

        return *this;
    }
}