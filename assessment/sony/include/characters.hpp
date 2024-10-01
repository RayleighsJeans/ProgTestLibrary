#pragma once

/// @brief Character (char*) type classification enumerator.
enum CharType
{
  None,         ///< Empty or no/unclassified character.
  Number,       ///< Arabic numeral.
  Operator,     ///< Operator of + - * /.
  OpenBracket,  ///< Opening/leading parentheses.
  CloseBracket, ///< Closing parentheses.
};
