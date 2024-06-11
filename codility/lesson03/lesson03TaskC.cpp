#include "../../include/header.hpp"


constexpr int N = 10;
constexpr int limit = 1000; // std::numeric_limits<int>::max();


using namespace helper;


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
  for (size_t P = 1; P < A.size(); P++) {
    diff = std::min(diff, std::abs(sumLeft - sumRight));

    sumLeft += A[P];
    sumRight -= A[P];
  }
  return diff;
} // solution


int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(-limit, limit);

  std::vector<int> vector;
  int result = -1;

  for (int i = 0; i < 10; i++) {
    vector = gen.randomVector(2, N);
    print<char[], int>("vector", vector);
    file(vector);

    result = solution(vector);
    print<char[], int>("result", result);
    file(result);
    file.flush();
  }
  return 0;
} // main
