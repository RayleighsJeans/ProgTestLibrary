#include <random>
#include <gtest/gtest.h>

#include "../include/evaluate.hpp"
#include "include/distributions.hpp"
#include "include/map.hpp"


using OperatorType = double (*)(const double&, const double&);

constexpr int MaxNumeral = 10000;

constexpr helper::CompileTimeMap<int, char, 4> OperatorCharMap = {
  {{0, '+'}, {1, '-'}, {2, '*'}, {3, '/'}}};

constexpr helper::CompileTimeMap<int, OperatorType, 4> OperatorMap = {
  {{0, math::operators::accumulate},
   {1, math::operators::subtract},
   {2, math::operators::multiply},
   {3, math::operators::divide}}};


class AutomaticTestPrimer : public testing::Test
{
 protected:
  helper::RandomDistribution<int> m_boolDist;
  helper::RandomDistribution<int> m_operatorDist;
  helper::RandomDistribution<int> m_charDist;
  helper::RandomDistribution<int> m_numberDist;
  std::mt19937 m_generator;

  std::vector<std::list<int>> numbers;
  std::vector<std::list<OperatorType>> operators;

 protected:
  AutomaticTestPrimer()
      : m_boolDist(helper::RandomDistribution<int>(0, 1)),
        m_operatorDist(helper::RandomDistribution<int>(0, 3)),
        m_charDist(helper::RandomDistribution<int>(1, 4)),
        m_numberDist(helper::RandomDistribution<int>(-MaxNumeral, MaxNumeral)),
        m_generator(std::mt19937((std::random_device())())) {};
  ~AutomaticTestPrimer() = default;

  int nextChar() { return m_charDist(m_generator); }
  int nextOp() { return m_operatorDist(m_generator); }
  int nextNumb() { return m_numberDist(m_generator); }
  int valid() { return m_boolDist(m_generator); }

  double calculate(std::list<double>& numbers,
                   std::list<OperatorType>& operators)
  {
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

    while (numberOfChars > 0) {
      if (lastChar == CharType::None) {
        switch (nextChar()) {
          case CharType::Number:
          {
            int thisNumber = nextNumb();
            numbers.push_back(thisNumber);
            output += std::to_string(thisNumber);
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
            int thisNumber = nextNumb();
            numbers.push_back(thisNumber);
            output += std::to_string(thisNumber);
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
    numberOfBrackets = 2; // m_numberDist(m_generator);
    while (numberOfBrackets * 3 > numberOfChars || numberOfBrackets < 0)
      numberOfBrackets = m_numberDist(m_generator);

    int bracketLevel = 0;
    std::string output =
      buildExpression(numberOfChars, numberOfBrackets, result, bracketLevel);
    return output;
  }

  std::string invalidExpression(int& result)
  {
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
      EXPECT_EQ((int)thisResult, testResult);
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