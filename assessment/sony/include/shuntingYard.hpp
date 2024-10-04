#pragma once

#include <math.h>
#include <deque>
#include <optional>
#include <string>
#include <tuple>
#include <vector>

#include "characters.hpp"
#ifdef _WIN32
#include "isfinite.hpp"
#endif


/// @brief Shunting-Yard algorithm:
/// >> "for parsing arithmetical or logical expressions,
///      or a combination of both, specified in infix notation"
/// source (22.09.24): https://en.wikipedia.org/wiki/Shunting_yard_algorithm
namespace shunting_yard
{
/// @brief Container object for Shunting-Yard character (description).
class Character
{
 public:
  /// @brief Shorthand for character type enumeration.
  using Type = CharType;

 private:
  Type m_type;          ///< This characters type.
  std::string m_string; ///< Actual character string.
  int m_priority;       ///< Precedence over other characters.
  bool m_right;         ///< Right side association.
  bool m_unary;         ///< Flag for unary type character.

 public:
  /// @brief ctor. Fill necessary variable fields.
  /// @param type Its type.
  /// @param s Its string.
  /// @param priority Its precedence (default -1).
  /// @param right Its right-hand-side association (default ).
  /// @param unary Its unary character flag.
  Character(Type type, const std::string& s, int priority = -1,
            bool right = false, bool unary = false)
      : m_type{type},
        m_string(s),
        m_priority{priority},
        m_right{right},
        m_unary{unary} {};

  /// @brief Get its type.
  /// @return The type.
  Type type() const { return m_type; }

  /// @brief Get the string.
  /// @return The string.
  std::string string() const { return m_string; }

  /// @brief Get its precedence.
  /// @return The priority.
  int priority() const { return m_priority; }

  /// @brief Get its right side association.
  /// @return Its precedence.
  bool right() const { return m_right; }

  /// @brief Get its unary character.
  /// @return Its unary-type flag.
  bool unary() const { return m_unary; }
};

/// @brief Parse std container expression to stack of usable Shunting-Yard
/// characters.
/// @param expression Desired expression.
/// @return Stack of parsed characters.
std::optional<std::deque<Character>> toCharacters(std::string& expression)
{
  std::deque<Character> characters;

  // Remember last know character.
  Character::Type lastCharacter = Character::Type::None;

  const std::string::iterator end = expression.end();
  for (std::string::iterator iterator = expression.begin();
       iterator != expression.end(); iterator++) {
    if (isblank(*iterator)) {
      // Pass blanks.
      continue;
    }
    else if (isdigit(*iterator)) {
      std::string::iterator start = iterator;

      // Concatenate multy-digit numbers
      while (iterator != end && (isdigit(*iterator) || *iterator == '.'))
        ++iterator;

      std::string thisString = std::string(start, iterator);
      characters.push_back(Character{Character::Type::Number, thisString});
      iterator--;

      if (lastCharacter == Character::Type::CloseBracket)
        // No bueno combination.
        return std::nullopt;
      lastCharacter = Character::Type::Number;
    }
    else {
      // Everything else is assumed to be operators/unaries/brackets.
      Character::Type type = Character::Type::None;
      int precedence = -1;
      bool rightAssociative = false;
      bool unary = false;

      char thisCharacter = *iterator;
      switch (thisCharacter) {
        case '(':
        {
          if (lastCharacter == Character::Type::CloseBracket ||
              lastCharacter == Character::Type::Number)
            // No bueno combination.
            return std::nullopt;

          type = Character::Type::OpenBracket;
          lastCharacter = type;
          break;
        }
        case ')':
        {
          if (lastCharacter == Character::Type::OpenBracket ||
              lastCharacter == Character::Type::Operator)
            // No bueno combination.
            return std::nullopt;

          type = Character::Type::CloseBracket;
          lastCharacter = type;
          break;
        }
        case '*':
        {
          type = Character::Type::Operator;
          precedence = 3;
          break;
        }
        case '/':
        {
          type = Character::Type::Operator;
          precedence = 3;
          break;
        }
        case '+':
        {
          type = Character::Type::Operator;
          precedence = 2;
          break;
        }
        case '-':
        {
          // If character is '-' is first preceded by another
          // or leading bracket, it's a unary '-'. Note: 'm' is special
          // name for unaries and has the highest precedence.
          if (characters.empty() ||
              characters.back().type() == Character::Type::Operator ||
              characters.back().type() == Character::Type::OpenBracket) {
            unary = true;
            thisCharacter = 'm';
            type = Character::Type::Operator;
            precedence = 5;
          }
          else {
            // Operator otherwise.
            type = Character::Type::Operator;
            precedence = 2;
          }
          break;
        }
        default:
        {
          if (thisCharacter != '\0')
            // Everything besides terminating char is not allowed.
            return std::nullopt;
          break;
        }
      }

      if (type == Character::Type::Operator) {
        if (lastCharacter == Character::Type::OpenBracket ||
            (!unary && (lastCharacter == Character::Type::None ||
                        lastCharacter == Character::Type::Operator)))
          // No bueno operator-like combinations.
          return std::nullopt;
        lastCharacter = type;
      }

      std::string thisString = std::string(1, thisCharacter);
      characters.push_back(
        Character{type, thisString, precedence, rightAssociative, unary});
    }
  }

  if (lastCharacter == Character::Type::Operator ||
      lastCharacter == Character::Type::OpenBracket)
    // No bueno end character.
    return std::nullopt;

  return characters;
}

/// @brief Shunting-Yard algorithm (e.g. see Djikstra et al.)
/// @param characters Stack of parsed character from the char/string expression.
/// @return Stack of computable operators and numbers (characters still).
std::optional<std::deque<Character>> shuntingYard(
  const std::deque<Character>& characters)
{
  std::deque<Character> queue;
  std::vector<Character> stack;

  for (Character character : characters) {
    switch (character.type()) {
      case Character::Type::Number:
      {
        // Numerals simply put through.
        queue.push_back(character);
        break;
      }
      case Character::Type::Operator:
      {
        Character operatorA = character;

        // Walking through stack and negotiating operator precedences.
        while (!stack.empty()) {
          Character operatorB = stack.back();

          // 1: operatorA is left-ass. and precedence is less or equal
          // 2: operatorA if right-ass. and precedence is less
          // -> pop operatorB off stack and move to output
          if ((!operatorA.right() &&
               operatorA.priority() <= operatorB.priority()) ||
              (operatorA.right() &&
               operatorA.priority() < operatorB.priority())) {
            stack.pop_back();
            queue.push_back(operatorB);
            continue;
          }
          break;
        }
        // Place remainder.
        stack.push_back(operatorA);
        break;
      }
      case Character::Type::OpenBracket:
      {
        // Left parentheses go to stack.
        stack.push_back(character);
        break;
      }
      case Character::Type::CloseBracket:
      {
        bool match = false;

        // Walk the stack until the character at the top is a left parenthesis.
        // All else go to the output queue directly.
        while (!stack.empty()) {
          queue.push_back(stack.back());
          stack.pop_back();
          if (!stack.empty() &&
              (stack.back().type() == Character::Type::OpenBracket)) {
            match = true;
            break;
          }
        }

        if (!match && stack.empty()) {
          // No matching left parentheses found, abort.
          return std::nullopt;
        }
        // Left parentheses atomatically removed.
        stack.pop_back();
        break;
      }
      default:
      {
        return std::nullopt;
      }
    }
  }

  while (!stack.empty()) {
    // If the stack top is a parentheses there is mismatched nesting.
    if (stack.back().type() == Character::Type::OpenBracket) {
      return std::nullopt;
    }

    // Pop onto the output queue.
    queue.push_back(std::move(stack.back()));
    stack.pop_back();
  }
  return queue;
}

/// @brief Calculation of an arithmetic result, using the
/// the Shunting-Yard approacha and infix notation to parse a
/// regular expression if valid and flag as false otherwise.
/// Allowed are numerals 0-9 and combinations thereof, * + - /, spaces.
/// Infs/NaNs will we cast as invalid also.
/// @param expression The presented expression.
/// @param result If valid, the computed result.
/// @return Validity flag.
bool compute(const char* expression, int& result)
{
  std::string phrase(expression);

  auto parsingResult = toCharacters(phrase);
  if (!parsingResult.has_value())
    // Failed parsing.
    return false;

  std::deque<Character> characters = parsingResult.value();
  if (characters.empty())
    // Empty, pass.
    return false;

  auto priorityQueue = shuntingYard(characters);
  if (!priorityQueue.has_value())
    // Failed Shunting-Yard queue-ing.
    return false;
  std::deque<Character> queue = priorityQueue.value();

  std::vector<double> stack;
  // Walk the queue and compute step-by-step by precedence.
  while (!queue.empty()) {
    const Character character = queue.front();
    queue.pop_front();
    switch (character.type()) {
      case Character::Type::Number:
      {
        /// @TODO: stol has limits for conversion from arb. numerals.
        stack.push_back(std::stod(character.string()));
        break;
      }
      case Character::Type::Operator:
      {
        if (character.unary()) {
          const double rhs = stack.back();
          stack.pop_back();
          switch (character.string()[0]) {
            // Special case to flag for unary-type characters.
            case 'm':
            {
              stack.push_back(-rhs);
              break;
            }
            default:
            {
              return false;
              break;
            }
          }
        }
        else {
          // Usual operators and calculate, replace in queue.
          const double rhs = stack.back();
          stack.pop_back();
          const double lhs = stack.back();
          stack.pop_back();

          switch (character.string()[0]) {
            default:
            {
              return false;
              break;
            }
            case '*':
            {
              stack.push_back(lhs * rhs);
              break;
            }
            case '/':
            {
              stack.push_back(lhs / rhs);
              break;
            }
            case '+':
            {
              stack.push_back(lhs + rhs);
              break;
            }
            case '-':
            {
              stack.push_back(lhs - rhs);
              break;
            }
          }
        }
        break;
      }
      default:
      {
        return false;
      }
    }
  }

  // NaN/inf check and int casts, debug before truncation.
  // Consider NaN/Inf invalid since e.g. 1 / 0 might syntactically
  // correct but still not a computable arithmetic expression.
  result = stack.back();
  if (!std::isfinite(stack.back())) {
    printf(">> Expression evaluates to NaN/Inf: %lf\n", stack.back());
    return false;
  }
  printf(
    ">> Valid expression with result %lf"
    " before integer truncation.\n",
    stack.back());
  ///@TODO: Truncation due to int cast limits result space heavily.
  result = (int)stack.back();
  return true;
}
} // namespace shunting_yard