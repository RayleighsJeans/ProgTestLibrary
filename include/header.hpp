#include <cmath>

#include <algorithm>
#include <limits>
#include <random>

#include <array>
#include <map>
#include <memory>
#include <stack>
#include <vector>

#include <fstream>
#include <iostream>

#include <chrono>


// Custom header files.
#include "distributions.hpp"
#include "map.hpp"


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


/// @brief Write vector to std::out.
/// @tparam T Arithmetic type.
/// @param vector Data container to write to stream.
template <typename T>
void expand(const std::vector<T>& vector)
{
  std::cout << "[";
  for (auto it = vector.begin(); it < vector.end(); it++) {
    std::cout << *it;
    if (it != vector.end() - 1)
      std::cout << ", ";
  }
  std::cout << "]";
} // print


/// @brief Printing function for a 1D vector.
/// @tparam T Arithmetic data type of vector.
/// @param vector The data container provided to print.
template <typename T>
void print(const std::vector<T>& vector)
{
  expand<T>(vector);
  std::cout << ";\n";
} // print


/// @brief
/// @tparam T
/// @param value
template <typename T>
void print(const T& value)
{
  std::cout << value;
  std::cout << ";\n";
} // print


/// @brief Printing function for a 2D vector.
/// @tparam T Arithmetic data type of vector.
/// @param vector The data container provided to print.
template <typename T>
void print(const std::vector<std::vector<T>>& vector)
{
  if (vector.empty() || vector[0].empty())
    return;

  auto outerSize = vector.size();

  std::cout << "[";
  for (size_t i = 0; i < outerSize; i++) {
    if (i != 0)
      std::cout << " ";
    // Use simple printing fuction
    // for 1D inside vector.
    expand<T>(vector[i]);

    if (i < outerSize - 1)
      std::cout << ",\n";
  }
  std::cout << "];\n";
} // print


/// @brief Printing a name and 2D vector.
/// @tparam T Arithmetic data type of vector.
/// @param name Name to prefix the vector.
/// @param vector The data container provided to print.
template <typename T>
void print(const char* name, const std::vector<std::vector<T>>& vector)
{
  std::cout << ">> " << name << ": ";
  print<T>(vector);
} // print

template <typename T>
void print(const char* name, const T& value)
{
  std::cout << ">> " << name << ": ";
  print<T>(value);
} // print


/// @brief Printing a name and 1D vector.
/// @tparam T Arithmetic data type of vector.
/// @param name Name to prefix the vector.
/// @param vector The data container provided to print.
template <typename T>
void print(const char* name, const std::vector<T>& vector)
{
  std::cout << ">> " << name << ": ";
  print<T>(vector);
} // print


template <typename T, typename U>
void print(const U& prefix, const std::vector<T>& vector)
{
  std::cout << ">> " << prefix << ": ";
  print<T>(vector);
} // print


void print(const char* name, std::string& string)
{
  std::cout << ">> " << name << ": " << string << std::endl;
} // print


template <typename T>
void print(const T& prefix, std::string& string)
{
  std::cout << ">> " << prefix << ": " << string << std::endl;
} // print


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

    auto outersize = vector.size();
    m_file << "[";
    for (int i = 0; i < outersize; i++) {
      // Use simple 1D vector writing algo.
      writeVector(vector[i]);
      if (i < outersize - 1)
        m_file << ", ";
    }
    m_file << "]";

    m_tabs = true;
  } // operator()

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
 public:
  /// @brief ctor. Set up random distribution and generator seed.
  /// @param min Maximum random number value.
  /// @param max Minimum random number value.
  RandomGenerator(const T min, const T max)
      : m_randomDistribution(RandomDistribution(min, max)),
        m_generator(std::mt19937((std::random_device())())){};

  /// @brief dtor.
  ~RandomGenerator() = default;


 public:
  /// @brief Generate a single random number.
  /// @return A single random number.
  T operator()() { return m_randomDistribution(m_generator); } // operator()


  /// @brief Build random number vector of given length.
  /// @param length Exact lenght of vector.
  /// @return The constructed container.
  std::vector<T> randomVector(const int length)
  {
    std::vector<T> vector(length);
    randomVector<T>(vector, m_randomDistribution);
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
  } // randomVectorN

  /// @brief Build a vector of random length with elements [0, length]
  /// @return A random vector.
  std::vector<T> randomVectorN()
  {
    int length = (*this)();
    return randomVectorN(length);
  } // randomVectorN

  /// @brief Build a vector of random length with elements [0, length-1]
  /// @return A random vector.
  std::vector<T> randomVectorN_1()
  {
    int length = (*this)();
    return randomVectorN_1(length);
  }

  /// @brief Build a vector of
  /// @param length
  /// @return
  std::vector<T> randomVectorN_1(const int length)
  {
    std::vector<T> vector(length);
    auto elementDistributionN_1 = RandomDistribution(0, length - 1);
    randomVector(vector, elementDistributionN_1);
    return vector;
  }


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


  /// @brief Build 2D random number vector (vector of vectors) exact length and height.
  /// @param length Minimum length of vector.
  /// @param height Maximum length of vector.
  /// @return The constructed container.
  std::vector<std::vector<T>> random2dVector(const int length, const int height)
  {
    std::vector<std::vector<T>> vector(height, std::vector<T>(length));
    for (int i = 0; i < height; i++) {
      // Using simple 1D vector construction routine.
      vector[i] = randomVector(length);
    }
    return vector;
  }; // random2dVector


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
  void randomVector(std::vector<T>& vector, RandomDistribution<T>& randDist)
  {
    for (int i = 0; i < vector.size(); i++) {
      vector[i] = randDist(m_generator);
    }
  } // randomVector


  /// @brief Random number distribution for generation given a seed.
  RandomDistribution<T> m_randomDistribution;
  /// @brief Seed generator for random numbers.
  std::mt19937 m_generator;
}; // class RandomGenerator


class Timer
{
 private:
  using time = std::chrono::high_resolution_clock::time_point;
  using clock = std::chrono::high_resolution_clock;


 public:
  Timer() : m_tick(clock::now()) { m_tocks.push_back(m_tick); };
  ~Timer() = default;


 public:
  void tick() { m_tick = clock::now(); };
  void tock()
  {
    m_tocks.push_back(clock::now());
    double duration = std::chrono::duration<double, std::milli>(
                        std::chrono::duration_cast<std::chrono::milliseconds>(
                          m_tocks.back() - m_tick))
                        .count();
    std::cout << ">> time past: " << duration << "ms;\n";
  }

 private:
  time m_tick;
  std::vector<time> m_tocks;

}; // class Timer
} // namespace helper
