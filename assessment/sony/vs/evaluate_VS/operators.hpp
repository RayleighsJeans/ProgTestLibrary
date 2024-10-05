#pragma once

namespace math
{
namespace operators
{
/// @brief Accumulative/summation (operator +) function.
/// @param a Addend one.
/// @param b Addend two.
/// @return Sum.
double accumulate(const double& a, const double& b)
{
  return (a + b);
};

/// @brief Multiplication (operator *) function.
/// @param a Multiplier one.
/// @param b Multiplier two.
/// @return Product.
double multiply(const double& a, const double& b)
{
  return (a * b);
};

/// @brief Division (operator /) function.
/// @param a Dividend.
/// @param b Divisor.
/// @return Quotient.
double divide(const double& a, const double& b)
{
  return (a / b);
};

/// @brief Subtraction (operator -) function.
/// @param a Minuend.
/// @param b Subtrahend.
/// @return Difference.
double subtract(const double& a, const double& b)
{
  return (a - b);
};
} // namespace operators
} // namespace math