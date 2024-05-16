#include "../../include/header.hpp"


constexpr int N = 10;
constexpr int limit = 1000; // std::numeric_limits<int>::max();


int solution(std::vector<int>& A)
{
  auto vectorSum = [](std::vector<int> vector)
  {
    int sum = 0;
    for (auto& a : vector)
      sum += a;
    return sum;
  };
  auto totalSum = vectorSum(A);

  int sumLeft = A[0];
  int sumRight = totalSum - A[0];

  int diff = std::abs(sumLeft - sumRight);
  for (int P = 1; P < A.size(); P++) {
    diff = std::min(diff, std::abs(sumLeft - sumRight));

    sumLeft += A[P];
    sumRight -= A[P];
  }
  return diff;
} // solution


int main()
{
  helper::WriteToFile<int> file(__FILE__);
  helper::RandomGenerator<int> gen(-limit, limit);

  std::vector<int> vector;
  int result = -1;

  for (int i = 0; i < 10; i++) {
    vector = gen.randomVector(2, N);
    helper::print("vector", vector);
    file(vector);

    result = solution(vector);
    helper::print("result", result);
    file(result);
    file.flush();
  }
  return 0;
} // main
