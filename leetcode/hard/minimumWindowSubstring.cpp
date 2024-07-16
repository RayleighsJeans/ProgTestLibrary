
#include "../../include/header.hpp"
#include "words.hpp"

constexpr int N = 10;     // 50000;
constexpr int limit = 10; // 1000000000;


using namespace helper;


std::string findSubstring(const std::map<char, int>& letterCount,
                          const int& totalCount, const std::string& word)
{
  std::string substring = "";
  std::map<char, int> map(letterCount);
  int counter = totalCount;

  for (auto& letter : word) {
    if (map.count(letter) && (map[letter] > 0)) {
      // Count down.
      map[letter]--;
      counter--;
    }

    if (counter < totalCount)
      // Counting this substring.
      substring.push_back(letter);
  }
  return (!counter ? substring : "");
}; // findSubstring


std::map<char, int> countLetters(const std::string word)
{
  std::map<char, int> map;
  for (auto& letter : word) {
    if (!map.count(letter)) {
      map[letter] = 1;
    }
    else {
      map[letter]++;
    }
  }
  return map;
}; // countLetters


const std::string solution(const std::string& s, const std::string& t)
{
  const size_t totalCount = t.length();

  const auto letterCount = countLetters(t);
  // print<char[], char, int>("letter count", letterCount);

  const std::string substring = findSubstring(letterCount, totalCount, s);
  if (substring.empty())
    return "";
  // print<char[], std::string>("substring", substring);

  auto subCount = countLetters(substring);
  // print<char[], char, int>("substring count", subCount);

  char letter;
  size_t start;
  for (start = 0; start < substring.length(); start++) {
    letter = substring[start];
    subCount[letter]--;
    if ((letterCount.count(letter) > 0)) {
      if ((subCount[letter] < letterCount.at(letter)))
        break;
    }
  }
  const std::string candidate = substring.substr(start, substring.length());

  int end;
  for (end = candidate.length() - 1; end >= 0; end--) {
    letter = candidate[end];
    subCount[letter]--;
    if ((letterCount.count(letter) > 0)) {
      if ((subCount[letter] < letterCount.at(letter)))
        break;
    }
  }

  // print<char[], char, int>("final sub count",
  //                          countLetters(candidate.substr(0, end)));
  return candidate.substr(0, end);
} // solution


std::string solutionC(std::string s, std::string t)
{
  if (s.empty() || t.empty() || s.length() < t.length()) {
    return "";
  }

  std::vector<int> map(128, 0);
  int count = t.length();
  int start = 0, end = 0, minLen = std::numeric_limits<int>::max(),
      startIndex = 0;

  for (char c : t) {
    map[c]++;
  }

  while (end < (int)s.length()) {
    if (map[s[end++]]-- > 0) {
      count--;
    }

    while (count == 0) {
      if (end - start < minLen) {
        startIndex = start;
        minLen = end - start;
      }

      if (map[s[start++]]++ == 0) {
        count++;
      }
    }
  }

  return minLen == std::numeric_limits<int>::max()
           ? ""
           : s.substr(startIndex, minLen);
} // solutionC


int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(-limit, limit);

  std::string a;
  std::string b;

  a = "ADOBECODEBANC";
  b = "ABC"; // BANC
  a = "a";
  b = "a"; // a
  a = "a";
  b = "aa"; // ""
  a = "bdab";
  b = "ab"; // ab
  a = "bba";
  b = "ab"; // ba
  a = LongSWord;
  b = LongTWord;

  std::string resultA, resultB;
  // print<char[], std::string>("string", a);
  // print<char[], std::string>("target", b);

  Timer t;
  t.tick();
  resultA = solutionC(a, b);
  t.tock();
  // print<char[], std::string>("result A", result);

  t.tick();
  resultB = solution(a, b);
  t.tock();
  // print<char[], std::string>("result B", result);

  return 0;
} // main