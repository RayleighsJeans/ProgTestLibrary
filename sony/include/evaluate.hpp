#pragma once

#include <list>
#include <string>
#include <optional>

#include "operators.hpp"


using OperatorType = int (*)(const int&, const int&);


bool isOperator(std::string::iterator& iterator,
                std::list<OperatorType>& operators)
{
  {
    using namespace math::operators;

    if (*iterator == '+') {
      operators.push_back(accumulate);
    }
    else if (*iterator == '-') {
      operators.push_back(subtract);
    }
    else if (*iterator == '*') {
      operators.push_back(multiply);
    }
    else if (*iterator == '/') {
      operators.push_back(divide);
    }
    else {
      return false;
    }
    return true;
  }
}


int countNumbers(std::string::iterator& iterator)
{
  std::string::iterator start = iterator;
  while (isdigit(*(iterator))) {
    iterator++;
  }
  return std::stoi(std::string(start, iterator));
}


bool isNumeral(std::string::iterator& iterator, std::list<int>& numbers)
{
  if (*iterator == '-') {
    if (isdigit(*(iterator + 1))) {
      iterator++;
      numbers.push_back(-1 * countNumbers(iterator));
      return true;
    }
  }
  else if (isdigit(*iterator)) {
    numbers.push_back(countNumbers(iterator));
    return true;
  }
  return false;
}


bool closingBracket(std::string::iterator& iterator)
{
  return (*iterator == ')');
}


bool leadingBracket(std::string::iterator& iterator)
{
  return (*iterator == '(');
}


int compute(std::list<int>& numbers,
            std::list<int (*)(const int&, const int&)>& operators)
{
  int result = numbers.front();
  numbers.pop_front();

  while (!operators.empty()) {
    result = operators.front()(result, numbers.front());
    operators.pop_front();
    numbers.pop_front();
  }
  return result;
}


std::optional<int> parse(std::string& expression,
                         std::string::iterator& iterator,
                         bool inParentheses = false)
{
  std::list<int> numbers;
  std::list<int (*)(const int&, const int&)> operators;

  for (; iterator < expression.end(); iterator++) {
    if (*iterator == ' ')
      continue;

    if (isNumeral(iterator, numbers)) {
      continue;
    }
    else if (isOperator(iterator, operators)) {
      continue;
    }
    else if (leadingBracket(iterator)) {
      iterator++;
      auto inBrackets = parse(expression, iterator, true);
      if (inBrackets.has_value()) {
        numbers.push_back(inBrackets.value());
      }
      else {
        return std::nullopt;
      }
    }
    else if (closingBracket(iterator)) {
      if (inParentheses) {
        iterator++;
        inParentheses = false;
        break;
      }
      else {
        return std::nullopt;
      }
    }
    else {
      return std::nullopt;
    }
  }

  if (inParentheses)
    return std::nullopt;

  if (numbers.size() != operators.size() + 1)
    return std::nullopt;
  return compute(numbers, operators);
}


bool evaluate(const char* expression, int& result)
{
  std::string phrase(expression);
  std::string::iterator start = phrase.begin();
  auto work = parse(phrase, start);
  if (work.has_value()) {
    result = work.value();
    return true;
  }
  return false;
}