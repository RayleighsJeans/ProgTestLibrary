#pragma once

#include <vector>

#include <fstream>
#include <iostream>


namespace helper
{
/// @brief Class container providing functionality to write to a file.
/// @tparam T Data type in containers stored in file.
template <typename T>
class WriteToFile
{
 private:
  /// @brief Txt file name.
  std::string m_fileName;
  /// @brief Following print action needs preceding tabs?
  bool m_tabs = false;
  /// @brief Output stream handle to file.
  std::ofstream m_file;

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
};  // class WriteToFile
} // namespace helper