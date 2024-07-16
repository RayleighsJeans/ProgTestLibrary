#pragma once

#include <vector>

namespace helper
{
/// @brief Print an arbitrary value (type).
/// @tparam T The value type.
/// @param value The value.
template <typename T>
void print(const T& value)
{
  std::cout << value;
  std::cout << ";\n";
} // print


/// @brief Print an arbitrary typed pair of values.
/// @tparam V First value type.
/// @tparam W Second value type.
/// @param pair The pair value.
template <typename V, typename W>
void print(const std::pair<V, W>& pair)
{
  std::cout << "{" << pair.first << "," << pair.second << "}";
} // print


/// @brief Write vector to std::out.
/// @tparam T Arithmetic type.
/// @param vector Data container to write to stream.
template <typename T>
void expand(const std::vector<T>& vector)
{
  std::cout << "[";
  for (auto it = vector.begin(); it < vector.end(); it++) {
    std::cout << *it;
    if (it != vector.end() - 1)
      std::cout << ", ";
  }
  std::cout << "]";
} // expand


/// @brief Write a vector of pairs to std::cout.
/// @tparam V First value type.
/// @tparam W Second value type.
/// @param vector Data container of pairs to output.
template <typename V, typename W>
void expand(const std::vector<std::pair<V, W>>& vector)
{
  std::cout << "[";
  for (size_t i = 0; i < vector.size(); i++) {
    print<V, W>(vector[i]);
    if (i != vector.size() - 1)
      std::cout << ", ";
  }
  std::cout << "]";
} // expand


/// @brief Printing a map with arbitrary types of key/value.
/// @tparam V Key data type.
/// @tparam W Value data type.
/// @param map The keyed data container.
template <typename V, typename W>
void expand(const std::map<V, W>& map)
{
  const int N = map.size();
  int i = -1;
  std::cout << "<";
  for (auto const& [key, value] : map) {
    i++;
    std::cout << "{" << key << ":" << value << "}";
    if (i < N - 1)
      std::cout << ", ";
  }
  std::cout << ">";
} // expand


/// @brief Printing function for a 1D vector.
/// @tparam T Arithmetic data type of vector.
/// @param vector The data container provided to print.
template <typename T>
void print(const std::vector<T>& vector)
{
  expand<T>(vector);
  std::cout << ";\n";
} // print


/// @brief Printing function for a 1D vector of pairs.
/// @tparam V First value type.
/// @tparam W Second value type.
/// @param vector Data container of pairs to put out.
template <typename V, typename W>
void print(const std::vector<std::pair<V, W>>& vector)
{
  expand<V, W>(vector);
  std::cout << ";\n";
} // expand


/// @brief Printing function for a 2D vector.
/// @tparam T Arithmetic data type of vector.
/// @param vector The data container provided to print.
template <typename T>
void print(const std::vector<std::vector<T>>& vector)
{
  if (vector.empty()) // || vector[0].empty())
    return;

  auto outerSize = vector.size();

  std::cout << "\n[";
  for (size_t i = 0; i < outerSize; i++) {
    if (i != 0)
      std::cout << " ";
    // Use simple printing fuction
    // for 1D inside vector.
    expand<T>(vector[i]);

    if (i < outerSize - 1)
      std::cout << ",\n";
  }
  std::cout << "];\n";
} // print


/// @brief Printing function for a 2D vector of pairs.
/// @tparam V First value type.
/// @tparam W Second value type.
/// @param vector Two-dimensional data container of pairs to put out.
template <typename V, typename W>
void print(const std::vector<std::vector<std::pair<V, W>>>& vector)
{
  if (vector.empty() || vector[0].empty())
    return;

  auto outerSize = vector.size();

  std::cout << "\n[";
  for (size_t i = 0; i < outerSize; i++) {
    if (i != 0)
      std::cout << " ";
    // Use simple printing fuction
    // for 1D inside vector.
    expand<V, W, std::pair<V, W>>(vector[i]);

    if (i < outerSize - 1)
      std::cout << ",\n";
  }
  std::cout << "];\n";
} // print


/// @brief Print a arbitrary value (type) with a prefix.
/// @tparam T The value type.
/// @param name The prefix.
/// @param value The value.
template <typename U, typename T>
void print(const U& name, const T& value)
{
  std::cout << ">> " << name << ": ";
  print<T>(value);
} // print


/// @brief Printing a name and 1D vector.
/// @tparam T Arithmetic data type of vector.
/// @param name Name to prefix the vector.
/// @param vector The data container provided to print.
template <typename U, typename T>
void print(const U& name, const std::vector<T>& vector)
{
  std::cout << ">> " << name << ": ";
  print<T>(vector);
} // print


/// @brief Printing a name and 2D vector.
/// @tparam U Prefix data type of name.
/// @tparam T Arithmetic data type of vector.
/// @param name Name to prefix the vector.
/// @param vector The data container provided to print.
template <typename U, typename T>
void print(const U& name, const std::vector<std::vector<T>>& vector)
{
  std::cout << ">> " << name << ": ";
  print<T>(vector);
} // print


/// @brief Printing a name and a pair of values.
/// @tparam U Prefix data type of name.
/// @tparam V First value type.
/// @tparam W Second value type.
/// @param name Name to prefix pair.
/// @param value The pair.
template <typename U, typename V, typename W>
void print(const U& name, const std::pair<V, W>& value)
{
  std::cout << ">> " << name << ": ";
  print<V, W>(value);
} // print


/// @brief Printing a name and a vector of pairs.
/// @tparam U Prefix data type of name.
/// @tparam V First value type.
/// @tparam W Second value type.
/// @param name Name to prefix vector.
/// @param value The pair vector.
template <typename U, typename V, typename W>
void print(const U& name, const std::vector<std::pair<V, W>>& value)
{
  std::cout << ">> " << name << ": ";
  print<V, W>(value);
} // print


/// @brief Printing a name and a 2D vector of pairs.
/// @tparam U Prefix data type of name.
/// @tparam V First value type.
/// @tparam W Second value type.
/// @param name Name to prefix vector.
/// @param vector The 2D pair vector.
template <typename U, typename V, typename W>
void print(const U& name,
           const std::vector<std::vector<std::pair<V, W>>>& vector)
{
  std::cout << ">> " << name << ": ";
  print<V, W>(vector);
} // print


/// @brief Printing a name and a map of keys/values.
/// @tparam U Prefix data type of name.
/// @tparam V Key data type.
/// @tparam W Value data type.
/// @param name Name to prefix vector.
/// @param map The 2D pair vector.
template <typename U, typename V, typename W>
void print(const U& name, const std::map<V, W>& map)
{
  std::cout << ">> " << name << ": ";
  expand<V, W>(map);
  std::cout << std::endl;
} // print


} // namespace helper