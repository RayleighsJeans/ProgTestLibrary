#pragma once

#include <cmath>
#include <random>

#include <map>
#include <vector>

#include <iostream>

#include "distributions.hpp"


namespace helper
{
/// @brief Random number generator class for arithmetic types.
/// @tparam T Arithmetic data type for randomization.
template <typename T>
class RandomGenerator
{
 private:
  T m_minimumValue;
  T m_maximumValue;

  /// @brief Random number distribution for generation given a seed.
  RandomDistribution<T> m_randomDistribution;
  /// @brief Binary true/false distribution for generation given a seed.
  RandomDistribution<int> m_binaryDistribution;
  /// @brief Seed generator for random numbers.
  std::mt19937 m_generator;

 public:
  T getMax() const { return m_maximumValue; };
  T getMin() const { return m_minimumValue; };

 public:
  /// @brief ctor. Set up random distribution and generator seed.
  /// @param min Maximum random number value.
  /// @param max Minimum random number value.
  RandomGenerator(const T min, const T max)
      : m_minimumValue(min),
        m_maximumValue(max),
        m_randomDistribution(RandomDistribution<T>(min, max)),
        m_binaryDistribution(RandomDistribution<int>(0, 1)),
        m_generator(std::mt19937((std::random_device())())){};

  /// @brief dtor.
  ~RandomGenerator() = default;


 public:
  /// @brief Generate a single random number.
  /// @return A single random number.
  T operator()() { return m_randomDistribution(m_generator); }; // operator()

  /// @brief Get a random true/false.
  /// @return A randomly distributed boolean true or false.
  bool trueFalse() { return m_binaryDistribution(m_generator); } // trueFalse

  /// @brief Build random number vector of given length.
  /// @param length Exact length of vector.
  /// @return The constructed container.
  std::vector<T> randomVector(const int length)
  {
    std::vector<T> vector(length);
    randomVector(vector, m_randomDistribution);
    return vector;
  }; // randomVector

  /// @brief Build a vector of @ref length with elements [0, length]
  /// @param length The total length of the vector.
  /// @return A random vector(length).
  std::vector<T> randomVectorN(const int length)
  {
    std::vector<T> vector(length);
    auto elementDistributionN = RandomDistribution(0, length);
    randomVector(vector, elementDistributionN);
    return vector;
  }; // randomVectorN

  /// @brief Build a vector of random length with elements [0, length]
  /// @return A random vector.
  std::vector<T> randomVectorN()
  {
    int length = (*this)();
    return randomVectorN(length);
  }; // randomVectorN

  /// @brief Build a vector of random length with elements [0, length-1]
  /// @return A random vector.
  std::vector<T> randomVectorN_1()
  {
    int length = (*this)();
    return randomVectorN_1(length);
  }; // randomVectorN_1

  /// @brief Build a vector of given length with elements [0, length-1]
  /// @param length The desired length.
  /// @return A random vector.
  std::vector<T> randomVectorN_1(const int length)
  {
    std::vector<T> vector(length);
    auto elementDistributionN_1 = RandomDistribution(0, length - 1);
    randomVector(vector, elementDistributionN_1);
    return vector;
  }; // randomVectorN_1

  /// @brief Build a random vector that potentially has a leader -
  ///        a number that occurs >= length/2 times.
  /// @param length The desired length.
  /// @return A vector with a potential leader.
  std::vector<T> randomLeaderVector(const int length)
  {
    float split = RandomDistribution<float>(0, 1)(m_generator);
    T leader = m_randomDistribution(m_generator);

    std::vector<T> vector(length);
    randomVector(vector, m_randomDistribution);

    for (int i = 0; i < length; i++) {
      if (i / (float)length < split) {
        vector[i] = leader;
      }
      else {
        break;
      }
    }

    std::shuffle(vector.begin(), vector.end(), m_generator);
    return vector;
  } // randomLeaderVector

  /// @brief Build random number vector of random length.
  /// @param minLength Minimum length of vector.
  /// @param maxLength Maximum length of vector.
  /// @return The constructed container.
  std::vector<T> randomVector(const int minLength, const int maxLength)
  {
    auto lengthDistribution = RandomDistribution(minLength, maxLength);
    // Using simple 1D vector construction routine.
    return randomVector(lengthDistribution(m_generator));
  }; // randomVector

  /// @brief Create a random number vector with unique numbers.
  /// @param length Length of that vector
  /// @return The created vector.
  std::vector<T> randomUniqueVector(const int length)
  {
    std::vector<T> vector(length);
    randomUniqueVector(vector, m_randomDistribution);
    return vector;
  }; // randomUniqueVector

  /// @brief Build 2D random number vector (vector of vectors) exact length and
  /// height.
  /// @param length Minimum length of vector.
  /// @param height Maximum length of vector.
  /// @return The constructed container.
  std::vector<std::vector<T>> randomNdVector(const int length, const int height)
  {
    std::vector<std::vector<T>> vector(height, std::vector<T>(length));
    for (int i = 0; i < height; i++) {
      // Using simple 1D vector construction routine.
      vector[i] = randomVector(length);
    }
    return vector;
  }; // randomNdVector

  std::vector<std::vector<T>> randomNdUniqueVector(const int length,
                                                   const int height)
  {
    bool oversized = ((length * height) > (m_maximumValue - m_minimumValue));
    bool overOversized = (height > (m_maximumValue - m_minimumValue));

    std::vector<std::vector<T>> vector(height, std::vector<T>(length));
    std::vector<T> startingValues;
    std::map<T, bool> map;

    for (int i = 0; i < height; i++) {
      std::vector<T> thisColumn(length);

      if (oversized) {
        if (i == 0)
          startingValues =
            (overOversized ? randomVector(height) : randomUniqueVector(height));
        map[startingValues[i]] = true;
      }

      if (oversized)
        thisColumn[0] = startingValues[i];

      // Using simple 1D vector construction routine.
      randomUniqueVector(map, thisColumn, m_randomDistribution);
      vector[i] = thisColumn;

      if (oversized)
        map.clear();
    }
    return vector;
  }; // randomNdVector


  /// @brief Build 2D random number vector (vector of vectors)
  ///        of random length and height.
  /// @param minLength Minimum length of vector.
  /// @param maxLength Maximum length of vector.
  /// @param minHeight Minimum height of vector.
  /// @param maxHeight Maximum height of vector.
  /// @return The constructed container.
  std::vector<std::vector<T>> random2dVector(const int minLength,
                                             const int maxLength,
                                             const int minHeight,
                                             const int maxHeight)
  {
    auto lengthDistribution = RandomDistribution(minLength, maxLength);
    auto heightDistribution = RandomDistribution(minHeight, maxHeight);
    // Using 2D vector construction routine.
    return random2dVector(lengthDistribution(m_generator),
                          heightDistribution(m_generator));
  }; // random2dVector


 private:
  /// @brief Create a random vector in-place of a provided container and with a
  /// given distribution.
  /// @param vector The container to fill.
  /// @param randDist The distribution from which values are generated.
  void randomVector(std::vector<T>& vector, RandomDistribution<T>& randDist)
  {
    for (size_t i = 0; i < vector.size(); i++) {
      vector[i] = randDist(m_generator);
    }
  }; // randomVector

  /// @brief Create vector of random, unique numbers in-place of container from
  /// a given distribution.
  /// @param map A hash map tracking already set numbers.
  /// @param vector The provided container (pre-sized).
  /// @param randDist The distribution.
  void randomUniqueVector(std::map<T, bool>& map, std::vector<T>& vector,
                          RandomDistribution<T>& randDist)
  {
    T number;
    int count = map.size();
    const int maxSize =
      (std::is_integral_v<T> ? m_maximumValue - m_minimumValue
                             : std::numeric_limits<int>::max());

    bool error = false;
    for (size_t i = 0; i < vector.size(); i++) {
      number = randDist(m_generator);

      if (count < maxSize) {
        while (map.find(number) != map.end()) {
          number = randDist(m_generator);
        }
      }
      else {
        if (!error) {
          error = true;
          std::cout << ">> \033[1;31mOverflow unique vector at step#" << i
                    << "\033[0m, continue randomization." << std::endl;
        }
      }

      vector[i] = number;
      map[number] = true;
      count++;
    }
  }; // randomUniqueVector

  /// @brief Create vector of random, unique numbers in-place of container from
  /// a given distribution.
  /// @param vector The provided container (pre-sized).
  /// @param randDist The distribution.
  void randomUniqueVector(std::vector<T>& vector,
                          RandomDistribution<T>& randDist)
  {
    std::map<int, bool> map;
    randomUniqueVector(map, vector, randDist);
  } // randomUniqueVector
};  // class RandomGenerator
} // namespace helper