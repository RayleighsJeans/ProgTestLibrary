#include "../../include/header.hpp"


constexpr int N = 10;
constexpr int limit = 10; // std::numeric_limits<int>::max();


int solution(std::vector<int>& A)
{
  if (A.empty())
    return 1;

  std::sort(A.begin(), A.end());
  if (A.front() > 1)
    return 1;

  for (size_t i = 0; i < A.size() - 1; i++) {
    if (A[i + 1] - A[i] > 1)
      return A[i] + 1;
  }
  return A.back() + 1;
} // solution


int main()
{
  helper::WriteToFile<int> file(__FILE__);
  helper::RandomGenerator<int> gen(1, limit);

  std::vector<int> vector;
  int result = -1;
  for (int i = 0; i < 10; i++) {
    vector.resize(gen());

    for (int i = 1; i <= vector.size(); i++)
      vector[i - 1] = i;

    helper::RandomGenerator<int> genB(0, vector.size() - 1);
    vector.erase(vector.begin() + genB());

    std::shuffle(vector.begin(), vector.end(),
                 std::default_random_engine{(std::random_device())()});
    helper::print("vector", vector);

    file(vector);
    result = solution(vector);
    helper::print("result", result);

    file(result);
    file.flush();
  }
  return 0;
} // main
