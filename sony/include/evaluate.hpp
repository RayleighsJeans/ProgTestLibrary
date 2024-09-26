#pragma once

#include <cmath>
#include <list>
#include <optional>
#include <string>

#include "characters.hpp"
#include "operators.hpp"


/// @brief Shorthand type for operator function signature.
using OperatorType = double (*)(const double&, const double&);

/// @brief Check if a given (pointer-to) character is an operator and remember.
/// @param iterator Pointer-to character to check.
/// @param operators List of operators to bookkeep this if found.
/// @return Was an operator found?
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

/// @brief Walk through an expression and concatenate a
/// larger number from individual digits.
/// @param iterator Pointer-to first character to check.
/// @return Long number found.
std::optional<double> countNumbers(std::string::iterator& iterator)
{
  std::string::iterator start = iterator;
  bool hasDecimal = false;
  while (isdigit(*iterator) || *iterator == '.') {
    if (*iterator == '.') {
      if (!hasDecimal)
        hasDecimal = true;

      else
        return std::nullopt;
    }
    iterator++;
  }
  /// @TODO: std::stod has its limits. Better way?
  return std::stod(std::string(start, iterator));
}

/// @brief Check if a given (pointer-to) character is a numeral and remember.
/// @param iterator Pointer-to character to check.
/// @param numbers List of numbers to bookkeep this if found.
/// @return Was a (longer) number found?
bool isNumeral(std::string::iterator& iterator, std::list<double>& numbers)
{
  // Leading - means unary and not operator.
  if (*iterator == '-') {
    if (isdigit(*(iterator + 1))) {
      iterator++;
      auto numeral = countNumbers(iterator);
      if (!numeral.has_value())
        return false;
      numbers.push_back(-1 * numeral.value());
      return true;
    }
  }
  else if (isdigit(*iterator)) {
    auto numeral = countNumbers(iterator);
    if (!numeral.has_value())
      return false;
    numbers.push_back(numeral.value());
    return true;
  }
  return false;
}

/// @brief Check if a given (pointer-to) character is a closing bracket.
/// @param iterator Pointer-to character to check.
/// @return Was a closing parentheses found?
bool closingBracket(std::string::iterator& iterator)
{
  return (*iterator == ')');
}

/// @brief Check if a given (pointer-to) character is a opening bracket.
/// @param iterator Pointer-to character to check.
/// @return Was a opening parentheses found?
bool leadingBracket(std::string::iterator& iterator)
{
  return (*iterator == '(');
}

/// @brief From a given list of numbers and operators, calculate
/// the result with respect to arithmetic laws (mnemonics).
/// @param numbers List of floating point numbers.
/// @param operators List of arithmetic operators.
/// @return The computed result.
double compute(std::list<double>& numbers, std::list<OperatorType>& operators)
{
  // First, do all multiplications/divisions and
  // replace/delete from both lists accordingly. Also left to right, no brackets
  // left here.
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

  // Finally, only +/- left, left to right.
  double result = numbers.front();
  numbers.pop_front();
  while (!operators.empty()) {
    result = operators.front()(result, numbers.front());
    operators.pop_front();
    numbers.pop_front();
  }
  return result;
}

/// @brief Parse a regular (in-/valid expression) to numbers and operators.
/// Works recursively for brackets.
/// @param expression Regular string expression to calculate result for.
/// @param iterator Starting (pointer-to) character to begin evaluation.
/// @param inParentheses Flag for evaluation inside brackets.
/// @return If valid expression, yield floating point results, else empty.
std::optional<double> parse(std::string& expression,
                            std::string::iterator& iterator,
                            bool inParentheses = false)
{
  std::list<double> numbers;
  std::list<OperatorType> operators;

  // Remember last known character, begins with none.
  CharType lastChar = CharType::None;
  // Remember current/last known good poiter-to
  // character for unaries/neg. numbers.
  std::string::iterator before;
  while (iterator < expression.end()) {
    before = iterator;

    // Pass on emtpy/space.
    if (*iterator == ' ') {
      iterator++;
      continue;
    }

    // Numbers have precedence.
    if (isNumeral(iterator, numbers)) {
      if (lastChar == CharType::Number || lastChar == CharType::CloseBracket) {
        if (numbers.back() > 0)
          // No good combination.
          return std::nullopt;
        else if (std::signbit(numbers.back())) {
          numbers.pop_back();
          // Should be operator instead of negative number.
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
        // No good combination.
        return std::nullopt;
      lastChar = CharType::Operator;
      iterator++;
      continue;
    }
    else if (leadingBracket(iterator)) {
      if (lastChar == CharType::CloseBracket)
        return std::nullopt;

      iterator++;
      // Recursively resolve expressions inside
      // parentheses so evaluation later becomes more easy.
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
        // No good combination.
        return std::nullopt;

      // If in recursive, i.e. in-parentheses mode,
      // finish up this level of nesting.
      if (inParentheses) {
        iterator++;
        inParentheses = false;
        break;
      }
      else {
        // Wrong nesting.
        return std::nullopt;
      }
    }
    else {
      // Unknown character.
      return std::nullopt;
    }
  }

  if (inParentheses)
    // Wrong nesting.
    return std::nullopt;

  // Unmatching number of numerals and operators.
  if (numbers.size() != operators.size() + 1)
    return std::nullopt;
  return compute(numbers, operators);
}

/// @brief Compute, if valid, an integer result for a
// given regular text containing arithmetic expressions
// etc. (numerals 0-9 and combinations thereof, * + - /, spaces).
// Infs/NaNs will we cast as invalid also.
/// @param expression Expression to evaluate.
/// @param result If valid, calculated result, potentially down-cast integer.
/// @return Flag if expression is valid for parsing/computation.
bool evaluate(const char* expression, int& result)
{
  // Iteration via. std container simpler.
  std::string phrase(expression);
  std::string::iterator start = phrase.begin();
  auto work = parse(phrase, start);

  // Check results.
  if (work.has_value()) {
    // Consider NaN/Inf invalid since e.g. 1 / 0 might syntactically
    // correct but still not a computable arithmetic expression.
    if (!std::isfinite(work.value())) {
      printf(">> Expression evaluates to NaN/Inf: %lf\n", work.value());
      return false;
    }

    printf(
      ">> Valid expression with result %lf"
      " before integer truncation.\n",
      work.value());
    ///@TODO: Truncation due to int cast limits result space heavily.
    result = (int)work.value();
    return true;
  }
  printf(">> Invalid expression passed.\n");
  return false;
}