#include "../include/header.hpp"

#include <optional>
#include "include/operators.hpp"


using namespace helper;

using namespace math::operators;

using OperatorType = int (*)(const int&, const int&);


bool isOperator(const char* expression, std::list<OperatorType>& operators)
{
  if (*expression == '+') {
    operators.push_back(accumulate);
  }
  else if (*expression == '-') {
    operators.push_back(subtract);
  }
  else if (*expression == '*') {
    operators.push_back(multiply);
  }
  else if (*expression == '/') {
    operators.push_back(divide);
  }
  else {
    return false;
  }
  return true;
}


bool isNumeral(const char* expression, std::list<int>& numbers)
{
  if (*expression == '-') {
    if (isdigit(*(expression + 1))) {
      numbers.push_back(-1 * (*(expression + 1) - '0'));
      return true;
    }
  }
  else if (isdigit(*expression)) {

    numbers.push_back(*expression - '0');
    return true;
  }
  return false;
}


bool closingBracket(const char* expression)
{
  return (*expression == ')');
}


bool leadingBracket(const char* expression)
{
  return (*expression == '(');
}


int compute(std::list<int>& numbers,
            std::list<int (*)(const int&, const int&)>& operators)
{
  int result = numbers.front();
  numbers.pop_front();

  while (!operators.empty()) {
    std::cout << result << " <> " << numbers.front() << std::endl;
    result = operators.front()(result, numbers.front());
    operators.pop_front();
    numbers.pop_front();
  }
  return result;
}


std::optional<int> inParentheses(const char* expression);


std::optional<int> parse(const char* expression)
{
  std::list<int> numbers;
  std::list<int (*)(const int&, const int&)> operators;

  while (*expression != '\0') {
    std::cout << *expression << std::endl;

    if (*expression == ' ') {
      expression++;
      continue;
    }

    if (isNumeral(expression, numbers)) {
      if (numbers.back() < 0)
        expression += 2;
      else
        expression++;
    }
    else if (isOperator(expression, operators)) {
      expression++;
    }
    else if (leadingBracket(expression)) {
      expression++;
      auto inBrackets = inParentheses(expression);
      if (inBrackets.has_value()) {
        numbers.push_back(inBrackets.value());
        while (!closingBracket(expression))
          expression++;
        expression++;
      }
      else {
        return false;
      }
    }
    else if (closingBracket(expression)) {
      expression++;
      break;
    }
    else {
      return std::nullopt;
    }
  }

  std::cout << "sizes " << numbers.size() << " " << operators.size()
            << std::endl;
  if (numbers.size() != operators.size() + 1)
    return std::nullopt;
  return compute(numbers, operators);
}


std::optional<int> inParentheses(const char* expression)
{
  return parse(expression);
}


bool evaluate(const char* expression, int& result)
{
  auto work = parse(expression);
  if (work.has_value()) {
    result = work.value();
    return true;
  }
  return false;
}


int main()
{
  // const char expression[] = "1 + 3";
  // const char expression[] = "1 + -3 + 3";
  // const char expression[] = "(1 + 3) * 2";
  // const char expression[] = "(4 / 2) + 6";
  const char expression[] = "4 + (12 / (1 * 2))";
  // const char expression[] = "(1 + (12 * 2)";

  int result;
  bool validity;

  validity = evaluate(expression, result);

  print<char[], bool>("validity", validity);
  print<char[], int>("result", result);
  return 0;
}
