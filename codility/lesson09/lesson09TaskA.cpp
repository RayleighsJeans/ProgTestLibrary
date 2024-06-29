#include "../../include/header.hpp"


constexpr int N = 10;     // 100000;
constexpr int limit = 10; // 10000;


using namespace helper;


int solution(std::vector<int>& A)
{
  if (A.size() == 2) {
    return (A[1] - A[0] > 0 ? A[1] - A[0] : 0);
  }

  std::vector<int> gains;
  gains.push_back(0);
  for (size_t i = 1; i < A.size(); i++) {
    gains.push_back(A[i] - A[i - 1]);
  }

  int max_slice = 0;
  int max_ending = 0;
  for (size_t j = 0; j < gains.size(); j++) {
    max_ending = std::max(0, max_ending + gains[j]);
    max_slice = std::max(max_slice, max_ending);

    print<char[], int>("ending", max_ending);
    print<char[], int>("slice", max_slice);
  }
  return max_slice;
} // solution

int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(-limit, limit);

  int result = -1;
  std::vector<int> vector = gen.randomVector(1, N);
  vector = {23171, 21011, 21123, 21366, 21013, 21367};
  // vector = {8, 9, 3, 6, 1, 2};
  print<char[], int>("vector", vector);

  Timer t;
  t.tick();
  result = solution(vector);
  t.tock();
  print<char[], int>("result", result);

  return 0;
} // main