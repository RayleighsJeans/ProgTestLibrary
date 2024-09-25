#include "../include/evaluate.hpp"


int main()
{
  std::string string = "2.3 + 4.5";
  int result;
  evaluate(string.c_str(), result);
  return 0;
}