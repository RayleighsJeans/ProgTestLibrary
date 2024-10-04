#include "../include/evaluate.hpp"


int main()
{
  std::string string = "2.3.2 + 4.5";
  int result;
  evaluate(string.c_str(), result);
  return 0;
}