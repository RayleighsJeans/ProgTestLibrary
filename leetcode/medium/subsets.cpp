#include "../../include/header.hpp"


constexpr int N = 20;     // 50000;
constexpr int limit = 50; // 1000000000;


using namespace helper;


std::vector<std::vector<int>> solution(std::vector<int>& A)
{
  const size_t N = A.size();
  std::vector<std::vector<int>> result;

  result.push_back(std::vector<int>());
  int K = 1;

  for (size_t i = 0; i < N; i++) {
    for (int j = 0; j < K; j++) {
      std::vector<int> tmp(result[j]);
      tmp.push_back(A[i]);
      result.push_back(tmp);
    }
    K += K;
  }
  return result;
} // solution


int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(1, N);

  std::vector<int> vector = gen.randomUniqueVector(N - 1);
  std::vector<std::vector<int>> result;

  // vector = {0};
  // vector = {1, 2, 3};
  // vector = {1, 2, 3, 4};
  // print<char[], int>("vector", vector);

  Timer t;
  t.tick();
  result = solution(vector);
  t.tock();
  // print<char[], int>("result", result);
  print<char[], int>("results size", result.size());
  print<char[], int>("should be", std::pow(2, vector.size()));

  return 0;
} // main