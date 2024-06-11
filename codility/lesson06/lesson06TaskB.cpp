#include "../../include/header.hpp"


using namespace helper;


constexpr int N = 10;     // 100000
constexpr int limit = 10; // std::numeric_limits<int>::max();


int solution(std::vector<int>& A)
{
  if (A.size() == 3)
    return (A[0] * A[1] * A[2]);

  std::sort(A.begin(), A.end());
  return std::max(A[0] * A[1] * A.back(),
                  A.back() * A[A.size() - 2] * A[A.size() - 3]);
} // solution


int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(-limit, limit);

  std::vector<int> vector;
  int result = 0;

  vector = gen.randomVector(3, N);
  vector = {-3, 1, 2, -2, 5, 6};

  print<char[], int>("vector", vector);
  result = solution(vector);
  print<char[], int>("result", result);

  return 0;
} // main
