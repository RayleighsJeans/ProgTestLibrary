#include "../../include/header.hpp"


using namespace helper;


constexpr int N = 10; // 100000
constexpr int M = 5;  // 50000

constexpr CompileTimeMap<char, int, 4> dnaMap{
  {{'A', 1}, {'C', 2}, {'G', 3}, {'T', 4}}};
constexpr CompileTimeMap<int, char, 4> invDnaMap{
  {{1, 'A'}, {2, 'C'}, {3, 'G'}, {4, 'T'}}};


std::vector<int> solution(std::string& S, std::vector<int>& P,
                          std::vector<int>& Q)
{
  std::vector<std::vector<int>> prefixSumAminos(
    4, std::vector<int>(S.size() + 1, 0));
  for (size_t i = 0; i < S.size(); i++) {
    prefixSumAminos[dnaMap[S[i]] - 1][i + 1] += 1;
    for (int j = 0; j < 4; j++)
      prefixSumAminos[j][i + 1] += prefixSumAminos[j][i];
  }

  std::vector<int> result(P.size(), -1);
  for (size_t i = 0; i < P.size(); i++) {
    if (prefixSumAminos[0][Q[i] + 1] - prefixSumAminos[0][P[i]] > 0)
      result[i] = 1;
    else if (prefixSumAminos[1][Q[i] + 1] - prefixSumAminos[1][P[i]] > 0)
      result[i] = 2;
    else if (prefixSumAminos[2][Q[i] + 1] - prefixSumAminos[2][P[i]] > 0)
      result[i] = 3;
    else if (prefixSumAminos[3][Q[i] + 1] - prefixSumAminos[3][P[i]] > 0)
      result[i] = 4;
  }
  return result;
} // solution


int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> genAmino(1, 4);

  std::vector<int> result;

  Timer t;
  t.tick();
  for (int i = 0; i < 10; i++) {

    std::string dna = "";
    for (auto& amino : genAmino.randomVector(1, N)) {
      dna += invDnaMap[amino];
    }

    const int K = dna.size();
    RandomGenerator<int> gen(0, K - 1);
    RandomGenerator<int> genB(1, M);
    std::vector<std::vector<int>> PQ(2, std::vector<int>());
    for (int i = 0; i < genB(); i++) {
      PQ[0].push_back(gen());
      PQ[1].push_back(gen());
      while (PQ[1].back() < PQ[0].back()) {
        PQ[1].pop_back();
        PQ[1].push_back(gen());
      }
    }

    print<char[], std::string>("DNA", dna);
    print<char[], int>("PQ", PQ);
    file(dna.c_str());
    file(PQ);
    result = solution(dna, PQ[0], PQ[1]);
    print<char[], int>("result", result);

    file(result);
    file.flush();
  }
  t.tock();

  return 0;
} // main