#pragma once


/* clang-format off

Task Description
================
interval_map<K,V> is a data structure that efficiently associates intervals of keys of type K with values of type V. Your task is to implement the assign member function of this data structure, which is outlined below.

interval_map<K, V> is implemented on top of std::map. In case you are not entirely sure which functions std::map provides, what they do and which guarantees they provide, we provide an excerpt of the C++ standard here: 

Each key-value-pair (k,v) in the std::map means that the value v is associated with the interval from k (including) to the next key (excluding) in the std::map.

Example: the std::map (0,'A'), (3,'B'), (5,'A') represents the mapping
0 -> 'A'
1 -> 'A'
2 -> 'A'
3 -> 'B'
4 -> 'B'
5 -> 'A'
6 -> 'A'
7 -> 'A'
... all the way to numeric_limits<int>::max()

The representation in the std::map must be canonical, that is, consecutive map entries must not have the same value: ..., (0,'A'), (3,'A'), ... is not allowed. Initially, the whole range of K is associated with a given initial value, passed to the constructor of the interval_map<K,V> data structure.

Key type K ---------------------------------------------------------------------
besides being copyable and assignable, is less-than comparable via operator<
is bounded below, with the lowest value being std::numeric_limits<K>::lowest()
does not implement any other operations, in particular no equality comparison or arithmetic operators

Value type V -------------------------------------------------------------------
besides being copyable and assignable, is equality-comparable via operator==
does not implement any other operations

clang-format on */


#include "keyType.hpp"
#include "valueType.hpp"

#include <assert.h>
#include <iostream>
#include <map>
#include <type_traits>


template <typename Key, typename Value>
class interval_map
{
 private:
  using V = think_cell::ValueType<Value>;
  using K = think_cell::KeyType<Key>;

  V m_valBegin;
  std::map<K, V> m_map;

 public:
  friend void IntervalMapTest();

  /// @brief ctor. Associates whole range of K with val.
  /// @param val Value to assign whole K with.
  interval_map(V const& value) : m_valBegin(value) {}

  /// @brief Get the starting value of this map.
  /// @return First range value.
  V valueBegin() const { return m_valBegin; }

  /// @brief Get a handle to this map.
  /// @return This map.
  const std::map<K, V>& map() const { return m_map; }

  /// @brief  Look-up of the value associated with a given key.
  /// @param key Desired key for lookup.
  /// @return Value at key.
  V const& operator[](K const& key) const
  {
    auto it = m_map.upper_bound(key);
    if (it == m_map.begin()) {
      return m_valBegin;
    }
    else {
      return (--it)->second;
    }
  } // operator[]

  /// @brief Assign value val to interval [keyBegin, keyEnd). Overwrite previous
  /// values in this interval. Conforming to the C++ Standard Library
  /// conventions, the interval includes keyBegin, but excludes keyEnd. If
  /// keyBegin >= eyEnd, his designates an empty interval, and assign must do
  /// nothing.
  /// @param keyBegin Range to assign with val beginning.
  /// @param keyEnd Range to assign with val end.
  /// @param val Valued to assign [keyBegin, keyEnd] to.
  void assign(const K& keyBegin, const K& keyEnd, const V& value)
  {
    if (!(keyBegin < keyEnd)) {
      return; // Trivial, see above.
    }

    // keyEnd == keyBegin - interval length 1 - could be entered,
    // However, type K definition in test does not provide further information
    // on possible iterations or operations.

    if (m_map.empty() || keyEnd < m_map.begin()->first) {
      // Trivial case; new interval is outside of existing ones.
      m_map.insert(std::make_pair(keyBegin, value));
      m_map.insert(std::make_pair(keyEnd, m_valBegin));
      return;
    }

    // Last key inside new interval.
    auto middleInterval = std::prev(m_map.upper_bound(keyEnd), 1);
    // First key inside new interval.
    auto lowerInterval = m_map.lower_bound(keyBegin);
    // First key outside new interval.
    auto upperInterval = m_map.upper_bound(keyEnd);

    // New interval (a,b) overlaps one (c,d) partially. (a < c < b < d)
    // New interval (a, b) overlaps multiple ((c,d), ..., (e, f)) partially.
    // (c < a < d < ... < e < b < f)
    auto residualValue = middleInterval->second;

    // Succeeding interval has same value.
    if (upperInterval->second == value) {
      upperInterval = std::prev(middleInterval, -1);
    }

    // Preceding interval does not have same value.
    if (lowerInterval == m_map.begin() ||
        !(std::prev(lowerInterval, 1)->second == value)) {
      // Delete in-between intervals and insert new one.
      m_map.erase(lowerInterval, upperInterval);
      m_map.insert(std::pair<K, V>(keyBegin, value));
    }
    else {
      // Matching value below, no need for new in-place interval.
      m_map.erase(lowerInterval, upperInterval);
    }

    // Succeeding interval has not same value,
    // reimplement old interval leftover.
    if (!(value == residualValue))
      m_map.insert(std::pair<K, V>(keyEnd, residualValue));
  } // assign

  /// @brief Operator for std iostream output handling.
  /// @param stream Output stream.
  /// @param map The relevant interval_map.
  /// @return Appended std iostream.
  friend std::ostream& operator<<(std::ostream& stream,
                                  const interval_map<Key, Value>& map)
  {
    int i = 0;
    for (auto it = map.map().begin(); it != map.map().end(); it++) {
      stream << i << " [" << it->first << ", ";
      stream << it->second << "]; ";
      i++;
    }
    return stream;
  } // operator<<

  /// @brief Print the associated map.
  void print() const { std::cout << *this << std::endl; } // print

  /// @brief Validation function - given the requirements - of the map.
  /// @return True or false for respective validity.
  bool validate() const
  {
    bool isOk = true;
    if (!m_map.empty()) {
      if (m_valBegin == m_map.begin()->second) {
        std::cout << "m_valBegin == m_map.begin()->second" << std::endl;
        isOk = false;
      }

      for (auto it = m_map.begin(); it != std::prev(m_map.end()); ++it) {
        if (it->second == std::next(it)->second) {
          std::cout << "it->second == std::next(it)->second" << std::endl;
          isOk = false;
        }
      }

      if (m_valBegin != std::prev(m_map.end())->second) {
        std::cout << "m_valBegin != std::prev(m_map.end())->second"
                  << std::endl;
        isOk = false;
      }
    }
    return isOk;
  } // validate

  /// @brief Assigning and asserting/testing the interval_map in itself.
  /// @param keyBegin Starting interval key.
  /// @param keyEnd End interval key.
  /// @param value Assigned value to interval.
  void assignTest(const K& keyBegin, const K& keyEnd, const V& value)
  {
    const interval_map<Key, Value> beforeIntervalMap(*this);

    assign(keyBegin, keyEnd, value);

    if (keyEnd < keyBegin) {
      assert(beforeIntervalMap.valueBegin() == m_valBegin);
      for (const auto& [k, v] : m_map)
        assert(beforeIntervalMap[k] == v);
    }
    else {
      if (beforeIntervalMap.map().empty()) {
        assert(this->operator[](keyBegin) == value);
        assert(this->operator[](keyEnd) == beforeIntervalMap.valueBegin());
        if constexpr (std::is_integral<Key>()) {
          assert(this->operator[](keyBegin - 1) ==
                 beforeIntervalMap.valueBegin());
          assert(this->operator[](keyEnd - 1) == value);
        }
      }
      else {
        if constexpr (std::is_integral<Key>()) {
          for (auto it = beforeIntervalMap.map().begin();
               it != beforeIntervalMap.map().end(); it++) {
            if (it->first < keyBegin || keyEnd < it->first) {
              assert(this->operator[](it->first) ==
                     beforeIntervalMap[it->first]);
            }
            if ((keyBegin < it->first) && (it->first < keyEnd)) {
              assert(this->operator[](it->first) == value);
            }
          }
        }
        else {
          for (const auto& [k, v] : m_map) {
            if (k < keyBegin || keyEnd < k) {
              assert(this->operator[](k) == beforeIntervalMap[k]);
            }
            if ((keyBegin < k) && (k < keyEnd)) {
              assert(this->operator[](k) == value);
            }
          }
        }
        assert(std::prev(beforeIntervalMap.map().end())->second ==
               beforeIntervalMap.valueBegin());
      }
    }
    assert(beforeIntervalMap.validate());
  } // assignTest
};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of int intervals to char.