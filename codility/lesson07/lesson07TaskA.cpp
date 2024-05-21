#include "../../include/header.hpp"


constexpr int N = 10; // 200000


using namespace helper;


constexpr CompileTimeMap<int, char, 3> BracketMapL = {
  {{0, '{'}, {1, '('}, {2, '['}}};
constexpr CompileTimeMap<char, int, 3> InvBracketMapL = {
  {{'{', 0}, {'(', 1}, {'[', 2}}};
constexpr CompileTimeMap<int, char, 3> BracketMapR = {
  {{0, '}'}, {1, ')'}, {2, ']'}}};


int solution(std::string& S)
{
  while (S.size() > 0) {
    if (S.size() == 1)
      return 0;

    auto match = BracketMapR[InvBracketMapL[S.front()]];

    if (InvBracketMapL.find(S[S.size() - 2]) &&
        (BracketMapR[InvBracketMapL[S[S.size() - 2]]] == S.back()))
      S.erase(S.size() - 2, 2);
    else if (match != S.back() && (match != S[1]))
      return 0;
    else {
      S.erase(0, 1);
      if (match == S.front())
        S.erase(0, 1);
      else if (match == S.back())
        S.erase(S.size() - 1);
    }
  }
  return 1;
} // solution


int solutionB(std::string& S)
{
  size_t M = S.size();
  std::vector<char> stash;

  for (size_t i = 0; i < N; i++) {
    if ((S[i] == '{') || (S[i] == '[') || (S[i] == '(')) {
      stash.push_back(S[i]);
    }
    else {
      if (stash.empty()) {
        return false;
      }
      char back = stash.back();
      stash.pop_back();
      if ((S[i] == ')') && (back != '(')) {
        return false;
      }
      if ((S[i] == ']') && (back != '[')) {
        return false;
      }
      if ((S[i] == '}') && (back != '{')) {
        return false;
      }
    }
  }
  return stash.empty();
}


int solutionC(std::string& S)
{
  std::vector<char> stash;
  for (size_t i = 0; i < S.size(); ++i) {
    char c = S[i];
    if (('(' == c) || ('{' == c) || ('[' == c)) {
      stash.push_back(c);
    }
    else {
      if (stash.empty())
        return 0;

      char t = stash.back();
      if ((('}' == c) && ('{' != t)) || ((']' == c) && ('[' != t)) ||
          ((')' == c) && ('(' != t)))
        return 0;
      stash.pop_back();
    }
  }

  if (stash.empty())
    return 1;
  else
    return 0;
}


int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(0, 2);
  RandomGenerator<int> genB(0, 1);

  std::string brackets;
  for (auto& s : gen.randomVector(0, N / 2)) {
    brackets.insert(0, std::string{BracketMapL[s]});
    if (genB())
      brackets.append(std::string{BracketMapR[s]});
    if (genB()) {
      size_t n = brackets.size() - 1;
      int m = n - (n / 2);
      int type = gen();
      brackets.insert(m, std::string{BracketMapR[s]});
      brackets.insert(m, std::string{BracketMapL[s]});
    }
  }

  // brackets = "{[()()]}"; // 1
  // brackets = "({{({}[]{})}}[]{})"; // 1
  // brackets = "()(()())((()())(()()))"; // 1

  std::cout << ">> brackets:" << brackets << std::endl;

  int result = -1;
  Timer t;
  t.tick();
  result = solutionC(brackets);
  t.tock();
  print("result", result);

  return 0;
}