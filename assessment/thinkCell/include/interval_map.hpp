#pragma once


#include <iostream>
#include <map>


template <typename K, typename V>
class interval_map
{
 private:
  V m_valBegin;
  std::map<K, V> m_map;

 public:
  friend void IntervalMapTest();

  /// @brief ctor. Associates whole range of K with val.
  /// @param val Value to assign whole K with.
  interval_map(V const& val) : m_valBegin(val) {}

  /// @brief Get the starting value of this map.
  /// @return First range value.
  V valueBegin() const { return m_valBegin; }

  /// @brief Get a handle to this map.
  /// @return This map.
  const std::map<K, V>& map() const { return m_map; }

  /// @brief Assign value val to interval [keyBegin, keyEnd). Overwrite previous
  /// values in this interval. Conforming to the C++ Standard Library
  /// conventions, the interval includes keyBegin, but excludes keyEnd. If
  /// keyBegin >= eyEnd, his designates an empty interval, and assign must do
  /// nothing.
  /// @param keyBegin Range to assign with val beginning.
  /// @param keyEnd Range to assign with val end.
  /// @param val Valued to assign [keyBegin, keyEnd] to.
  void assign(K const& keyBegin, K const& keyEnd, V const& val)
  {
    if (!(keyBegin < keyEnd)) {
      return; // Trivial, see above.
    }

    // keyEnd == keyBegin - interval length 1 - could be entered,
    // However, type K definition in test does not provide further information
    // on possible iterations or operations.

    if (m_map.empty() || keyEnd < m_map.begin()->first) {
      // Trivial case; new interval is outside of existing ones.
      m_map.insert(std::make_pair(keyBegin, val));
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
    if (upperInterval->second == val) {
      upperInterval = std::prev(middleInterval, -1);
    }

    // Preceding interval does not have same value.
    if (lowerInterval == m_map.begin() ||
        !(std::prev(lowerInterval, 1)->second == val)) {
      // Delete in-between intervals and insert new one.
      m_map.erase(lowerInterval, upperInterval);
      m_map.insert(std::pair<K, V>(keyBegin, val));
    }
    else {
      // Matching value below, no need for new in-place interval.
      m_map.erase(lowerInterval, upperInterval);
    }

    // Succeeding interval has not same value,
    // reimplement old interval leftover.
    if (!(val == residualValue))
      m_map.insert(std::pair<K, V>(keyEnd, residualValue));
  } // assign

  /// @brief Print the associated map.
  void printMap() const
  {
    int i = 0;
    for (const auto& [key, value] : m_map) {
      std::cout << i << " [" << key << ", " << value << "]; ";
      i++;
    }
    std::cout << "\n";
  } // printMap

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

      for (auto it = m_map.begin(); it != prev(m_map.end()); ++it) {
        if (it->second == next(it)->second) {
          std::cout << "it->second == next(it)->second" << std::endl;
          isOk = false;
        }
      }

      if (m_valBegin != prev(m_map.end())->second) {
        std::cout << "m_valBegin != prev(m_map.end())->second" << std::endl;
        isOk = false;
      }
    }
    return isOk;
  } // validate


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
};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of int intervals to char.