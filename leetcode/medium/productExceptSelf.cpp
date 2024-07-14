#include "../../include/header.hpp"


constexpr int N = 100;    // 50000;
constexpr int limit = 10; // 1000000000;


using namespace helper;


std::vector<int> solutionA(std::vector<int>& B)
{
  size_t N = B.size();
  std::vector<int> A(N);
  std::copy(B.begin(), B.end(), A.begin());

  std::vector<int> P(N, 1);
  std::vector<std::pair<int, int>> leftRightP(N, std::pair<int, int>(1, 1));
  for (size_t i = 1; i < N; i++) {
    leftRightP[i].first = leftRightP[i - 1].first * A[i - 1];
  }

  for (int i = N - 1; i >= 0; i--) {
    if (i < (int)(N - 1))
      leftRightP[i].second *= A[i + 1] * leftRightP[i + 1].second;
    P[i] = leftRightP[i].first * leftRightP[i].second;
  }
  return P;
} // solution


std::vector<int> solutionB(std::vector<int>& B)
{
  std::vector<int> A(B.size());
  std::copy(B.begin(), B.end(), A.begin());

  std::vector<int> P(A.size());
  for (size_t i = 0; i < A.size(); i++) {
    P[i] = [&A, &i]() -> int
    {
      if (i == 0)
        return 1;
      int result = 1;
      for (size_t j = 0; j < i; j++) {
        result *= A[j];
      }
      return result;
    }() * [&A, &i]() -> int
    {
      if (i == A.size() - 1)
        return 1;
      int result = 1;
      for (size_t j = i + 1; j < A.size(); j++) {
        result *= A[j];
      }
      return result;
    }();
  }
  return P;
} // solution


int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(1, limit);

  std::vector<int> vector = gen.randomVector(N);
  std::vector<int> result(vector.size(), -1);

  // vector = {1, 2, 3, 4}; // {24,12,8,6}
  // vector = {-1, 1, 0, -3, 3}; // {0,0,9,0,0}
  print<char[], int>("vector", vector);

  Timer t;
  t.tick();
  result = solutionA(vector);
  t.tock();
  print<char[], int>("result A", result);

  t.tick();
  result = solutionB(vector);
  t.tock();
  print<char[], int>("result B", result);

  return 0;
} // main