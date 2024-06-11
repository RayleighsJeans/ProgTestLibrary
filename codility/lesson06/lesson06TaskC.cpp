#include "../../include/header.hpp"


using namespace helper;


constexpr int N = 10;     // 100000
constexpr int limit = 10; // std::numeric_limits<int>::max();


int solution(std::vector<int>& A)
{
  if (A.size() < 3)
    return 0;

  std::sort(A.begin(), A.end(), std::greater<int>());
  for (size_t i = 0; i < A.size() - 2; i++) {
    if (A[i] < 0)
      return 0;
    if (A[i] < A[i + 1] + A[i + 2]) {
      return 1;
    }
  }
  return 0;
} // solution


int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(-limit, limit);

  std::vector<int> vector;
  int result = 0;

  vector = gen.randomVector(3, N);
  vector = {10, 2, 5, 1, 8, 20};

  print<char[], int>("vector", vector);
  result = solution(vector);
  print<char[], int>("result", result);

  return 0;
} // main
