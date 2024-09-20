#pragma once

#include <functional>


namespace math
{
class Operators
{
 private:
  std::function<int(int, int)> accumulate = [](const int& a, const int& b)
  {
    return (a + b);
  };

  std::function<int(int, int)> multiply = [](const int& a, const int& b)
  {
    return (a * b);
  };

  std::function<int(int, int)> divide = [](const int& a, const int& b)
  {
    return (a / b);
  };

  std::function<int(int, int)> subtract = [](const int& a, const int& b)
  {
    return (a - b);
  };
} // class Operators
} // namespace math