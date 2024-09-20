#include "../include/header.hpp"


using namespace helper;


bool evaluateParantheses(const char* expression, int& result) {}


bool evaluate(const char* expression, int& result)
{
  result = -1;

  std::list<int> numbers;
  std::list<std::function<int(int, int)>*> operators;


  return false;
}


int main()
{
  const char expression[] = "1 + 3";
  // const char expression[] = "1 + 3) * 2";
  // const char expression[] = "(4 / 2) + 6";
  // const char expression[] = "4 + (12 / (1 * 2))";
  // const char expression[] = "(1 + (12 * 2)";

  int result;
  bool validity;

  validity = evaluate(expression, result);

  print<char[], bool>("validity", validity);
  print<char[], int>("result", result);
  return 0;
}
