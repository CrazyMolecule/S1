#include "Element.h"

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

bool Element::isDigit()
{
    for (char c : m_Value)
    {
        if (!std::isdigit(c))
            return false;
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