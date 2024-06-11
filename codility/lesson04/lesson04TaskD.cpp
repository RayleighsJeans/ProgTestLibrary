
#include "../../include/header.hpp"


constexpr int N = 10;     // 100000;
constexpr int limit = 10; // 1000000;


using namespace helper;


int solution(std::vector<int>& A)
{
  if (A.empty())
    return 1;
  if (A.size() == 1)
    return (((A[0] > 1) || (A[0] <= 0)) ? 1 : 2);

  std::sort(A.begin(), A.end());
  if (A[0] >= 2)
    return 1;

  for (size_t i = 0; i < A.size() - 1; i++) {
    if (std::abs(A[i + 1] - A[i]) > 1) {
      if ((A[i] + 1) <= 0) {
        if (A[i + 1] > 1) {
          return 1;
        }
        else {
          continue;
        }
      }
      return A[i] + 1;
    }
  }
  return ((A.back() < 1) ? 1 : A.back() + 1);
} // solution


int main()
{
  WriteToFile<int> file(__FILE__);

  RandomGenerator<int> gen(-limit, limit);

  int result = -1;
  std::vector<int> vector;

  Timer t;
  t.tick();
  for (int i = 0; i < 10; i++) {
    vector = gen.randomVector(1, N);

    file(vector);
    print<char[], int>("vector", vector);
    result = solution(vector);
    print<char[], int>("result", result);
    file(result);
    file.flush();
  }
  t.tock();

  return 0;
} // main