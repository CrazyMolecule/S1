#include <string>
#include <iostream>

#ifndef ELEMENT_H
#define ELEMENT_H
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

    Element() noexcept;
    Element(const Element&) noexcept;
    Element(std::string);
    Element(char);

    explicit operator long long() const;
    Element& operator= (const Element&) noexcept;

    bool isDigit() const;
    int getOperatorId() const;
    Type getType() const noexcept;
    std::string getElement() const noexcept;
    long long calculate(long long, long long) const;

  private:
    std::string m_Value;
    Type m_Type;

    bool isOpenParenthesis() const;
    bool isCloseParenthesis() const;
    bool isOperators() const;
  };
  using element = Element;
}
#endif
