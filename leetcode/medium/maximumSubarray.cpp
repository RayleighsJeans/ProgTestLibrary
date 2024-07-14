#include "../../include/header.hpp"


constexpr int N = 100;    // 50000;
constexpr int limit = 10; // 1000000000;


using namespace helper;


int solutionSum(std::vector<int>& A)
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


int solutionProduct(std::vector<int>& A)
{
  int max = std::numeric_limits<int>::min();
  int P = 1;

  for (size_t i = 0; i < A.size(); i++) {
    P *= A[i];
    max = std::max(P, max);
    if (P == 0)
      P = 1;
  }

  P = 1;
  for (size_t i = A.size() - 1; i >= 0; i--) {
    P *= A[i];
    max = std::max(P, max);
    if (P == 0)
      P = 1;
  }

  return max;
} // solution


int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(-limit, limit);

  std::vector<int> vector = gen.randomVector(N);
  int result;

  vector = {-2, 1, -3, 4, -1, 2, 1, -5, 4}; // 6
  vector = {1};                             // 1
  vector = {5, 4, -1, 7, 8};                // 23

  vector = {2, 3, -2, 4}; // 6
  vector = {-2, 0, -1};   // 0
  vector = {-2, 3, -4};   // 3
  print<char[], int>("vector", vector);

  Timer t;
  //   t.tick();
  //   result = solutionSum(vector);
  //   t.tock();
  //   print<char[], int>("result", result);

  t.tick();
  result = solutionProduct(vector);
  t.tock();
  print<char[], int>("result", result);

  return 0;
} // main