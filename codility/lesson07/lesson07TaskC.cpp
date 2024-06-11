#include "../../include/header.hpp"


constexpr int N = 2000000; // 100000


using namespace helper;


constexpr CompileTimeMap<int, char, 3> BracketMapL = {{{0, '('}}};
constexpr CompileTimeMap<char, int, 3> InvBracketMapL = {{{'(', 0}}};
constexpr CompileTimeMap<int, char, 3> BracketMapR = {{{0, ')'}}};


int solutionA(std::string& S)
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
  std::vector<char> stash;
  for (size_t i = 0; i < S.size(); ++i) {
    char c = S[i];
    if ('(' == c) {
      stash.push_back(c);
    }
    else {
      if (stash.empty())
        return 0;

      char t = stash.back();
      if ((')' == c) && ('(' != t))
        return 0;
      stash.pop_back();
    }
  }

  if (stash.empty())
    return 1;
  else
    return 0;
} // solutionC


int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(0, 1);
  RandomGenerator<int> genB(0, 1);

  int result = -1;
  std::string brackets;

  for (auto& s : gen.randomVector(0, N / 2)) {
    brackets.insert(0, std::string{BracketMapL[s]});
    if (genB())
      brackets.append(std::string{BracketMapR[s]});
    if (genB()) {
      size_t n = brackets.size() - 1;
      int m = n - (n / 2);
      brackets.insert(m, std::string{BracketMapR[s]});
      brackets.insert(m, std::string{BracketMapL[s]});
    }
  }

  //   brackets = "(()(())())";
  //   brackets = "())";

  //   print<char[], std::string>("brackets", brackets);
  Timer t;
  t.tick();
  result = solutionA(brackets);
  t.tock();
  print<char[], int>("result", result);

  t.tick();
  result = solutionB(brackets);
  t.tock();
  print<char[], int>("result", result);

  return 0;
} // main