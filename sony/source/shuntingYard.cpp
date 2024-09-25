#include "../include/shuntingYard.hpp"


int main()
{
  std::string expression = "2.3 - 4.5";
  int result;
  shunting_yard::compute(expression.c_str(), result);
  return 0;
}