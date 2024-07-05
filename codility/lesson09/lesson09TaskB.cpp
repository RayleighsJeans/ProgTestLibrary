#include "../../include/header.hpp"


constexpr int N = 10;     // 100000;
constexpr int limit = 10; // 10000;


using namespace helper;


int solution(std::vector<int>& A)
{
  int M = A.size();

  std::vector<int> sliceSum(M, 0);
  sliceSum[0] = A[0];
  for (int i = 1; i < M; i++)
    sliceSum[i] = std::max(sliceSum[i - 1] + A[i], A[i]);
  print<char[], int>("slice", sliceSum);

  int maxSlice = sliceSum[0];
  for (int i = 1; i < M; i++)
    maxSlice = std::max(maxSlice, sliceSum[i]);

  return maxSlice;
} // solution

int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(-limit, limit);

  int result = -1;
  std::vector<int> vector = gen.randomVector(1, N);
  // vector = {3, 2, -6, 4, 0}; // 5
  // vector = {0}; // 0
  // vector = {-2, -3, 4, -1, -2, 1, 5, -3}; // 7
  // vector = {-10}; // -10
  // vector = {1, 1}; // 2
  // vector = {5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5}; // 15
  vector = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5}; // 15
  print<char[], int>("vector", vector);

  Timer t;
  t.tick();
  result = solution(vector);
  t.tock();
  print<char[], int>("result", result);

  return 0;
} // main