#pragma once

#include <iostream>


namespace think_cell
{
template <typename BaseType>
class KeyType
{
 public:
  BaseType m_key;

 private:
  using K = KeyType<BaseType>;

  K assign(const K& other)
  {
    if (this != &other) { // handle self assignment
      m_key = other;      // copy assignment
    }
    return *this;
  };

 public:
  KeyType(const BaseType& key) : m_key(key){};
  KeyType(const K& key) : m_key(key.m_key){};

  K& operator=(const K& other) { return assign(other); }; // copy assignment
  K operator=(const K other) { return assign(other); };   // pass-by-value

  bool operator<(const K& other) const { return (m_key < other.m_key); }

  friend std::ostream& operator<<(std::ostream& stream, const K& key)
  {
    return (stream << key.m_key);
  }

  template <typename T = BaseType>
  typename std::enable_if<std::is_integral<T>::value, KeyType<T>>::type
  operator-(const int& value) const
  {
    return (m_key - value);
  }

  template <typename T = BaseType>
  typename std::enable_if<std::is_integral<T>::value, KeyType<T>>::type
  operator-(const K& other) const
  {
    return (m_key - other.m_key);
  }
};
} // namespace think_cell