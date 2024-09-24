#include "../include/evaluate.hpp"
#include <iostream>

int main()
{
  std::string string = "-9783(1617-1376(((*(";
  int result;
  evaluate(string.c_str(), result);
  return 0;
}