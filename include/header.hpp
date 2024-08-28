#pragma once

#include <cmath>

#include <algorithm>
#include <limits>
#include <random>

#include <array>
#include <list>
#include <map>
#include <memory>
#include <stack>

#include <fstream>
#include <iostream>

#include <chrono>


// Custom header files.
#include "distributions.hpp"
#include "map.hpp"
#include "printSuite.hpp"


namespace helper
{
/// @brief Finding a pointer to the maximum value element in a 2d vector.
/// @tparam T Arithmetic data type of vector
/// @param vector The data container provided to look in.
/// @return Handle to the maximum value element.
template <typename T>
typename std::vector<T>::iterator max_element(
  std::vector<std::vector<T>>& vector)
{
  typename std::vector<T>::iterator max = vector.begin()->begin();
  for (typename std::vector<std::vector<T>>::iterator it = vector.begin();
       it != vector.end(); it++) {
    for (typename std::vector<T>::iterator jt = it->begin(); jt != it->end();
         jt++) {
      if (*jt > *max)
        max = jt;
    }
  }
  return max;
} // max_element


/// @brief Class container providing functionality to write to a file.
/// @tparam T Data type in containers stored in file.
template <typename T>
class WriteToFile
{
 public:
  /// @brief ctor. Open files, stores (ostream) handle.
  /// @param path Base path to write the file to.
  WriteToFile(const char* path) : m_fileName(preparePath(path))
  {
    m_file.open(m_fileName.c_str(), std::ios_base::app);
  };

  /// @brief dtor. Close file again.
  ~WriteToFile() { m_file.close(); };


 private:
  /// @brief Prepare path by remove *.cpp and appending *.txt.
  /// @param path Original program cpp path.
  /// @return Text file path for storage.
  std::string preparePath(const char* path)
  {
    std::string file = path;
    file = file.substr(0, file.find(".cpp"));
    file += ".txt";
    return file;
  } // preparePath


 public:
  /// @brief
  /// @param characters
  void operator()(const char* characters)
  {
    if (!m_file.is_open())
      return;
    if (m_tabs)
      m_file << "\t\t";
    m_file << characters;
    m_tabs = true;
  } // operator

  /// @brief operator() overload. Write vector contents to txt.
  /// @param vector The data container.
  void operator()(const std::vector<T>& vector)
  {
    if (!m_file.is_open())
      return;
    if (m_tabs)
      m_file << "\t\t";
    writeVector(vector);
    m_tabs = true;
  } // operator()

  /// @brief operator() overload. Write 2D vector contents to txt.
  /// @param vector The data container.
  void operator()(const std::vector<std::vector<T>>& vector)
  {
    if (!m_file.is_open())
      return;
    if (m_tabs)
      m_file << "\t\t";

    size_t outersize = vector.size();
    m_file << "[";
    for (size_t i = 0; i < outersize; i++) {
      // Use simple 1D vector writing algo.
      writeVector(vector[i]);
      if (i < outersize - 1)
        m_file << ", ";
    }
    m_file << "]";

    m_tabs = true;
  } // operator()

  /// @brief Writing a value to the held file.
  /// @param value The value.
  void operator()(const T& value)
  {
    if (!m_file.is_open())
      return;
    if (m_tabs)
      m_file << "\t\t";
    m_file << value;
    m_tabs = true;
  }

  /// @brief Break line in txt file.
  void flush()
  {
    if (!m_file.is_open())
      return;
    m_file << "\n";
    m_tabs = false;
  } // flush


 private:
  /// @brief Simple 1D vector writing routine to txt file.
  /// @param vector Vector data container.
  void writeVector(const std::vector<T>& vector)
  {
    m_file << "[";
    for (size_t it = 0; it < vector.size(); it++) {
      m_file << vector.at(it);
      if (it != vector.size() - 1)
        m_file << ", ";
    }
    m_file << "]";
  } // writeVector


 private:
  /// @brief Txt file name.
  std::string m_fileName;
  /// @brief Following print action needs preceding tabs?
  bool m_tabs = false;
  /// @brief Output stream handle to file.
  std::ofstream m_file;
}; // class WriteToFile


/// @brief Random number generator class for arithmetic types.
/// @tparam T Arithmetic data type for randomization.
template <typename T>
class RandomGenerator
{
 private:
  T m_minimumValue;
  T m_maximumValue;

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
        m_generator(std::mt19937((std::random_device())())) {};

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
  }; // randomUniqueVector

  /// @brief Random number distribution for generation given a seed.
  RandomDistribution<T> m_randomDistribution;
  /// @brief Binary true/false distribution for generation given a seed.
  RandomDistribution<int> m_binaryDistribution;
  /// @brief Seed generator for random numbers.
  std::mt19937 m_generator;
}; // class RandomGenerator


/// @brief A helper object that measures and prints the time between tick() and
/// tock() and holds a lists of points in time.
class Timer
{
 private:
  using time = std::chrono::high_resolution_clock::time_point;
  using clock = std::chrono::high_resolution_clock;


 public:
  /// @brief ctor. Start the timer.
  Timer() : m_tick(clock::now()) { m_tocks.push_back(m_tick); };

  /// @brief dtor. Nothing.
  ~Timer() = default;


 public:
  /// @brief Start the timer (restart if starting point already exists).
  void tick() { m_tick = clock::now(); };

  /// @brief Measure the timer and remember the 'lap time'.
  void tock()
  {
    m_tocks.push_back(clock::now());
    double duration = std::chrono::duration<double, std::milli>(
                        std::chrono::duration_cast<std::chrono::milliseconds>(
                          m_tocks.back() - m_tick))
                        .count();
    std::cout << ">> time past: " << duration << "ms;\n";
  } // tock

 private:
  /// @brief The starting point (in time).
  time m_tick;
  /// @brief List of the stopped timers/lap times.
  std::vector<time> m_tocks;
}; // class Timer
} // namespace helper
