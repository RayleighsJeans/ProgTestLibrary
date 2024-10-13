#include <algorithm>
#include <bitset>


std::string ltrim(const std::string& str)
{
  std::string s(str);

  s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                  not1(std::ptr_fun<int, int>(isspace))));

  return s;
}

std::string rtrim(const std::string& str)
{
  std::string s(str);

  s.erase(
    find_if(s.rbegin(), s.rend(), not1(std::ptr_fun<int, int>(isspace))).base(),
    s.end());

  return s;
}
