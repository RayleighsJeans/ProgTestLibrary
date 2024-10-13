#pragma once


#include <iostream>


namespace think_cell
{
template <typename BaseType>
class ValueType
{
 public:
  BaseType m_value;

 private:
  using V = ValueType<BaseType>;
  using os = std::ostream;

  V assign(const V& other)
  {
    if (this != &other) { // handle self assignment
      m_value = other;    // copy assignment
    }
    return *this;
  };

 public:
  ValueType(const BaseType& value) : m_value(value){};
  ValueType(const V& value) : m_value(value.m_value){};

  V& operator=(const V& other) { return assign(other); }; // copy assignment
  V operator=(const V other) { return assign(other); };   // pass-by-value

  bool operator==(const V& other) const { return (m_value == other.m_value); }

  friend os& operator<<(os& stream, const V& v)
  {
    return (stream << v.m_value);
  }
};
} // namespace think_cell