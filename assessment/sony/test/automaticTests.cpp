#include <random>
#include <gtest/gtest.h>

#include "../include/evaluate.hpp"
#include "../include/shuntingYard.hpp"

#include "include/distributions.hpp"
#include "include/map.hpp"


/// @brief Shorthand type for operator function signature.
using OperatorType = double (*)(const double&, const double&);

/// @brief Maximum number of characters per expression (operators and numerals).
/// Also the maximum value of a singular numeral.
constexpr int MaxNumeral = 10000;

/// @brief A compile-time constant expression map object for the operator
/// characters.
constexpr helper::CompileTimeMap<int, char, 4> OperatorCharMap = {
  {{0, '+'}, {1, '-'}, {2, '*'}, {3, '/'}}};

/// @brief A compile-time constant expression map object for the operator
/// functions.
constexpr helper::CompileTimeMap<int, OperatorType, 4> OperatorMap = {
  {{0, math::operators::accumulate},
   {1, math::operators::subtract},
   {2, math::operators::multiply},
   {3, math::operators::divide}}};

/// @brief Test and regular expression class object for automatic testing.
class AutomaticTestPrimer : public testing::Test
{
 protected:
  helper::RandomDistribution<int>
    m_boolDist; ///< True/false random distribution.
  helper::RandomDistribution<int>
    m_operatorDist; ///< Random operator hash distribution.
  helper::RandomDistribution<int>
    m_charDist; ///< Random character hash distribution
  helper::RandomDistribution<double>
    m_numberDist; ///< Random number (numeral) distribution.
  std::mt19937 m_generator;

 protected:
  /// @brief ctor. Configuring the random distributions.
  AutomaticTestPrimer()
      : m_boolDist(helper::RandomDistribution<int>(0, 1)),
        m_operatorDist(helper::RandomDistribution<int>(0, 3)),
        m_charDist(helper::RandomDistribution<int>(1, 4)),
        m_numberDist(
          helper::RandomDistribution<double>(-MaxNumeral, MaxNumeral)),
        m_generator(std::mt19937((std::random_device())())) {};
  ~AutomaticTestPrimer() = default;

  /// @brief Get a key/hash for the next random character.
  /// @return The hash/key.
  int nextChar() { return m_charDist(m_generator); }

  /// @brief Get a key/hash for the next random operator.
  /// @return The hash/key.
  int nextOp() { return m_operatorDist(m_generator); }

  /// @brief Get a key/hash for the next random numeral.
  /// @return The hash/key.
  double nextNumb() { return m_numberDist(m_generator); }

  /// @brief Get random true/false.
  /// @return The hash/key.
  int valid() { return m_boolDist(m_generator); }

  /// @brief From a given list of numbers and operators, calculate
  /// the result with respect to arithmetic laws (mnemonics).
  /// @param numbers List of floating point numbers.
  /// @param operators List of arithmetic operators.
  /// @return The computed result.
  double calculate(std::list<double>& numbers,
                   std::list<OperatorType>& operators)
  {
    // First, do all multiplications/divisions and
    // replace/delete from both lists accordingly. Also left to right, no
    // brackets left here.
    auto num = numbers.begin();
    auto op = operators.begin();
    while (op != operators.end() && num != numbers.end()) {
      if (*op == math::operators::divide || *op == math::operators::multiply) {
        auto next = num;
        std::advance(next, 1);
        double prio = (*op)(*num, *next);

        op = operators.erase(op);
        numbers.erase(next);
        std::list<double>::iterator P = numbers.erase(num);
        num = numbers.insert(P, prio);
      }
      else {
        op++;
        num++;
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

  std::string buildExpression(int& numberOfChars, int& numberOfBrackets,
                              double& result, int& bracketLvl)
  {
    std::string output = "";

    std::list<double> numbers;
    std::list<OperatorType> operators;

    CharType lastChar = CharType::None;
    OperatorType lastOperator = math::operators::accumulate;

    // While still characters to put down, do so in allowed order,
    // i.e. correct arithmetic notation left to right, with proper nesting.
    // Also track numbers and operators at the same time
    // and do so recursively for inside brackets.
    while (numberOfChars > 0) {
      if (lastChar == CharType::None) {
        switch (nextChar()) {
          case CharType::Number:
          {
            double thisNumber = nextNumb();
            output += std::to_string(thisNumber);
            // Casting issues with doubles/string/ints.
            numbers.push_back(std::stod(std::to_string(thisNumber)));
            lastChar = CharType::Number;
            numberOfChars--;
            break;
          }
          case CharType::OpenBracket:
          {
            if (!numberOfBrackets)
              continue;
            output += "(";
            numberOfBrackets--;
            bracketLvl++;

            double thisResult;
            // Inside parentheses and resolve recursively.
            output += buildExpression(numberOfChars, numberOfBrackets,
                                      thisResult, bracketLvl);
            numbers.push_back(thisResult);
            lastChar = CharType::Number;
            break;
          }
          default:
            break;
        }
      }
      else if (lastChar == CharType::Number) {
        switch (nextChar()) {
          case CharType::Operator:
          {
            int thisOperator = nextOp();
            lastOperator = OperatorMap[thisOperator];
            operators.push_back(lastOperator);

            output += OperatorCharMap[thisOperator];
            lastChar = CharType::Operator;
            numberOfChars--;
            break;
          }
          case CharType::CloseBracket:
          {
            if (bracketLvl > 0 && numbers.size() > 1) {
              output += ")";
              lastChar = CharType::CloseBracket;
            }
            break;
          }
          default:
            break;
        }
      }
      else if (lastChar == CharType::Operator) {
        switch (nextChar()) {
          case CharType::Number:
          {
            double thisNumber = nextNumb();
            output += std::to_string(thisNumber);
            // Casting issues with doubles/string/ints.
            numbers.push_back(std::stod(std::to_string(thisNumber)));
            lastChar = CharType::Number;
            numberOfChars--;
            break;
          }
          case CharType::OpenBracket:
          {
            if (!numberOfBrackets)
              continue;
            output += "(";
            numberOfBrackets--;
            bracketLvl++;

            double thisResult;
            // Resolve inside parentheses recursively.
            output += buildExpression(numberOfChars, numberOfBrackets,
                                      thisResult, bracketLvl);
            numbers.push_back(thisResult);
            lastChar = CharType::Number;
            break;
          }
          default:
            break;
        }
      }
      else if (lastChar == CharType::CloseBracket) {
        // Keep going after last bracket if needed or finish up.
        if (numberOfChars > 0 && !bracketLvl) {
          int thisOperator = nextOp();
          lastOperator = OperatorMap[thisOperator];
          operators.push_back(lastOperator);
          output += OperatorCharMap[thisOperator];
          lastChar = CharType::Operator;
          numberOfChars--;
        }
        else {
          bracketLvl--;
          result = calculate(numbers, operators);
          return output;
        }
      }
    }

    while (bracketLvl > 0) {
      output += ")";
      bracketLvl--;
    }

    result = calculate(numbers, operators);
    return output;
  }

  std::string validExpression(double& result)
  {
    int numberOfChars;
    numberOfChars = m_numberDist(m_generator);
    while (!(numberOfChars % 2) || numberOfChars < 0)
      numberOfChars = m_numberDist(m_generator);

    int numberOfBrackets;
    numberOfBrackets = m_numberDist(m_generator);
    while (numberOfBrackets * 3 > numberOfChars || numberOfBrackets < 0)
      numberOfBrackets = m_numberDist(m_generator);

    // Generate expression like above and pass.
    int bracketLevel = 0;
    std::string output =
      buildExpression(numberOfChars, numberOfBrackets, result, bracketLevel);
    return output;
  }

  std::string invalidExpression(int& result)
  {
    // Randomnly concatenate a string that is made
    // out of the allowed, randomized characters in invalid order.
    std::string output;
    for (int i = 0; i < MaxNumeral; i++) {
      if (valid()) {
        if (valid()) // number
          output += std::to_string(nextNumb());
        else // operator
          output += OperatorCharMap[nextChar()];
      }
      else {
        if (valid()) // open bracket
          output += "(";
        else // close bracket
          output += ")";
      }
    }

    result = nextNumb();
    return output;
  }
};


TEST_F(AutomaticTestPrimer, ValidTest)
{
  double thisResult;
  int testResult;
  std::string expression;
  bool validity;

  for (int i = 0; i < 1000; i++) {
    expression = validExpression(thisResult);
    validity = evaluate(expression.c_str(), testResult);

    if (std::isfinite(thisResult)) {
      EXPECT_TRUE(validity);
      int results = (int)thisResult;
      EXPECT_EQ(results, testResult);
    }
    else {
      EXPECT_FALSE(validity);
    }
  }
}

TEST_F(AutomaticTestPrimer, InvalidTest)
{
  int thisResult;
  int testResult;
  std::string expression = invalidExpression(thisResult);
  bool validity = evaluate(expression.c_str(), testResult);
  EXPECT_FALSE(validity);
  EXPECT_NE(thisResult, testResult);
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}