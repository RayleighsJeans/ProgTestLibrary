#pragma once

#include <list>
#include <string>
#include <optional>

#include "operators.hpp"


using OperatorType = double (*)(const double&, const double&);

enum CharType
{
  None,
  Number,
  Operator,
  OpenBracket,
  CloseBracket
};


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


double countNumbers(std::string::iterator& iterator)
{
  std::string::iterator start = iterator;
  while (isdigit(*(iterator))) {
    iterator++;
  }
  return (double)std::stol(std::string(start, iterator));
}


bool isNumeral(std::string::iterator& iterator, std::list<double>& numbers)
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


double compute(std::list<double>& numbers, std::list<OperatorType>& operators)
{
  std::list<double>::iterator numIterator = numbers.begin();
  std::list<OperatorType>::iterator opIterator = operators.begin();
  while (opIterator != operators.end() && numIterator != numbers.end()) {
    if (*opIterator == math::operators::divide ||
        *opIterator == math::operators::multiply) {
      auto nextNumber = numIterator;
      std::advance(nextNumber, 1);
      double priorityResult = (*opIterator)(*numIterator, *nextNumber);

      opIterator = operators.erase(opIterator);
      numbers.erase(nextNumber);
      std::list<double>::iterator position = numbers.erase(numIterator);
      numIterator = numbers.insert(position, priorityResult);
    }
    else {
      opIterator++;
      numIterator++;
    }
  }

  double result = numbers.front();
  numbers.pop_front();
  while (!operators.empty()) {
    result = operators.front()(result, numbers.front());
    operators.pop_front();
    numbers.pop_front();
  }
  return result;
}


std::optional<double> parse(std::string& expression,
                            std::string::iterator& iterator,
                            bool inParentheses = false)
{
  std::list<double> numbers;
  std::list<OperatorType> operators;

  CharType lastChar = CharType::None;

  std::string::iterator before;
  while (iterator < expression.end()) {
    before = iterator;

    if (*iterator == ' ') {
      iterator++;
      continue;
    }

    if (isNumeral(iterator, numbers)) {
      if (lastChar == CharType::Number || lastChar == CharType::CloseBracket) {
        if (numbers.back() > 0)
          return std::nullopt;
        else if (std::signbit(numbers.back())) {
          numbers.pop_back();
          if (isOperator(before, operators)) {
            lastChar = CharType::Operator;
            iterator = before;
            iterator++;
          }
        }
      }
      else {
        lastChar = CharType::Number;
      }
      continue;
    }
    else if (isOperator(iterator, operators)) {
      if (lastChar == CharType::Operator || lastChar == CharType::None)
        return std::nullopt;
      lastChar = CharType::Operator;
      iterator++;
      continue;
    }
    else if (leadingBracket(iterator)) {
      if (lastChar == CharType::CloseBracket)
        return std::nullopt;

      iterator++;
      auto inBrackets = parse(expression, iterator, true);
      if (inBrackets.has_value()) {
        numbers.push_back(inBrackets.value());
        lastChar = CharType::CloseBracket;
      }
      else {
        return std::nullopt;
      }
    }
    else if (closingBracket(iterator)) {
      if (lastChar == CharType::None)
        return std::nullopt;

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
    if (!std::isfinite(work.value())) {
      printf(">> Expression evaluates to NaN/Inf: %lf\n", work.value());
      return false;
    }

    printf(
      ">> Valid expression with result %lf"
      " before integer truncation.\n",
      work.value());
    result = (int)work.value();
    return true;
  }
  printf(">> Invalid expression passed.\n");
  return false;
}