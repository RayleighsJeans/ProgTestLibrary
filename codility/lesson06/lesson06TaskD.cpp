#include "../../include/header.hpp"


constexpr int N = 10;     // 100000
constexpr int limit = 10; // std::numeric_limits<int>::max();


using namespace helper;


int solution(std::vector<int>& A)
{
  if (A.empty())
    return 0;

  int counter = 0;
  const size_t m = A.size();

  std::vector<std::vector<int>> discs(m, std::vector<int>(2, 0));
  for (size_t i = 0; i < A.size(); i++) {
    discs[i][0] = i - A[i];
    discs[i][1] = i + A[i];
  }

  auto sortLambda = [](const std::vector<int>& a, const std::vector<int>& b)
  {
    return a[0] < b[0];
  };

  std::sort(discs.begin(), discs.end(), sortLambda);

  for (size_t j = 0; j < m; j++) {
    for (size_t k = j + 1; ((k < m) && (discs[j][1] >= discs[k][0])); k++) {
      counter++;
      if (counter > 10000000)
        return -1;
    }
  }
  return counter;
} // solution


int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(-limit, limit);

  int result = -1;
  std::vector<int> vector = gen.randomVector(0, N);

  // rndVector = {1, 5, 2, 1, 4, 0};
  // rndVector = {3, 0, 1, 6};

  print("vector", vector);
  result = solution(vector);
  print("result", result);

  return 0;
} // main