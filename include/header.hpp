#pragma once

#include <algorithm>
#include <limits>

#include <array>
#include <list>
#include <memory>
#include <stack>

// Custom header files.
#include "compileMap.hpp"
#include "fileIO.hpp"
#include "printSuite.hpp"
#include "randGenerators.hpp"
#include "timer.hpp"


namespace helper
{
/// @brief Finding a pointer to the maximum value element in a 2d vector.
/// @tparam T Arithmetic data type of vector
/// @param vector The data container provided to look in.
/// @return Handle to the maximum value element.
template <typename T>
typename std::vector<T>::iterator max_element(
  std::vector<std::vector<T>>& vector)
{
  typename std::vector<T>::iterator max = vector.begin()->begin();
  for (typename std::vector<std::vector<T>>::iterator it = vector.begin();
       it != vector.end(); it++) {
    for (typename std::vector<T>::iterator jt = it->begin(); jt != it->end();
         jt++) {
      if (*jt > *max)
        max = jt;
    }
  }
  return max;
} // max_element
} // namespace helper
