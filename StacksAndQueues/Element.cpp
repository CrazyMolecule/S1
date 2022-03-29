#include "Element.h"
#include <cmath>

namespace bavykin
{
  Element::Element() noexcept
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
    else
    {
      throw std::logic_error("Given expression is incorrect (expected a digit, parenthesis or an operator).");
    }
  }

  Element::Element(char value)
  {
    char* arr = new char[1];
    arr[0] = value;
    Element n(arr);
  }

  Element::Element(const Element& value) noexcept
  {
    m_Value = value.m_Value;
    m_Type = value.m_Type;
  }

  bool Element::isDigit() const
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

  bool Element::isOpenParenthesis() const
  {
    return '(' == m_Value[0];
  }

  bool Element::isCloseParenthesis() const
  {
    return ')' == m_Value[0];
  }

  bool Element::isOperators() const
  {
    return getOperatorId() != -1;
  }

  int Element::getOperatorId() const
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

  Element::Type Element::getType() const noexcept
  {
    return m_Type;
  }

  std::string Element::getElement() const noexcept
  {
    return m_Value;
  }

  long long Element::calculate(long long a, long long b) const
  {
    long long c = 0;
    bool overflow = false;

    switch (m_Value[0])
    {
    case '+':
      c = a + b;
      overflow = static_cast<double>(a) + static_cast<double>(b) != static_cast<double>(a + b);
      break;
    case '-':
      c = a - b;
      overflow = static_cast<double>(a) - static_cast<double>(b) != static_cast<double>(a - b);
      break;
    case '*':
      c = a * b;
      overflow = static_cast<double>(a) * static_cast<double>(b) != static_cast<double>(a * b);
      break;
    case '/':
      if (b == 0)
      {
        throw std::logic_error("Division by zero!");
      }
      overflow = trunc(static_cast<double>(a) / static_cast<double>(b)) != static_cast<double>(a / b);
      c = a / b;
      break;
    case '%':
      if (b == 0)
      {
        throw std::logic_error("Division by zero!");
      }
      c = ((a % b) + b) % b;
      break;
    }

    if (overflow)
    {
      throw std::overflow_error("The resulting value is too large (overflow type long long)!");
    }

    return c;
  }

  Element::operator long long() const
  {
    if (m_Type != Type::digit)
    {
      throw std::logic_error("Not correct transform!");
    }

    long long out = 0;

    for (char c : m_Value)
    {
      out = out * 10 + (c - '0');
    }

    return out;
  }

  Element& Element::operator=(const Element& value) noexcept
  {
    m_Value = value.m_Value;
    m_Type = value.m_Type;

    return *this;
  }
}
