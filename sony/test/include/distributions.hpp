#pragma once

#include <type_traits>

namespace helper
{
template <typename T>
using dist_t = std::conditional_t<
  std::is_integral_v<T>,
  std::conditional_t<std::is_signed_v<T>,
                     std::uniform_int_distribution<long long>,
                     std::uniform_int_distribution<unsigned long long>>,
  std::uniform_real_distribution<T>>;

template <typename T,
          typename =
            typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class RandomDistribution
{
 private:
  T m_maximumValue;
  T m_minimumValue;

 public:
  RandomDistribution(T min, T max)
      : m_maximumValue(max),
        m_minimumValue(min),
        m_distribution(dist_t<T>(min, max)){};
  ~RandomDistribution() = default;

  T operator()(std::mt19937& generator) { return m_distribution(generator); };

 private:
  dist_t<T> m_distribution;
};
} // namespace helper