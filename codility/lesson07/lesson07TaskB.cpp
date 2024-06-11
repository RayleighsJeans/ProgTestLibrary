#include "../../include/header.hpp"


constexpr int N = 10;     // 200000
constexpr int limit = 10; // std::numeric_limits<int>::max();


using namespace helper;


int solution(std::vector<int>& A, std::vector<int>& B)
{
  if (A.empty() || B.empty())
    return 0;

  std::pair<std::vector<int>, std::vector<int>> fish;
  for (size_t i = 0; i < A.size(); i++) {
    if (B[i]) {
      fish.first.push_back(A[i]);
    }
    else {
      while (!(fish.first.empty()) && (fish.first.back() < A[i])) {
        fish.first.pop_back();
      }
      if (fish.first.empty())
        fish.second.push_back(A[i]);
    }
  }

  print("downstream", fish.first);
  print("upstream", fish.second);

  return fish.first.size() + fish.second.size();
}


int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(0, limit);
  RandomGenerator<int> genB(0, 1);

  std::vector<int> A;
  std::vector<int> B;

  const int M = gen();
  A = gen.randomUniqueVector(M);
  B = genB.randomVector(M);

  // A = {4, 3, 2, 1, 5};
  // B = {0, 1, 0, 1, 0};
  // A = {1, 2};
  // B = {0, 1};

  int result = -1;
  print<char[], int>("vector A", A);
  print<char[], int>("vector B", B);
  Timer t;
  t.tick();
  result = solution(A, B);
  t.tock();
  print<char[], int>("result", result);

  return 0;
}