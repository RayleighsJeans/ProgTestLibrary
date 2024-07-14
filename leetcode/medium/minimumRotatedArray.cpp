#include "../../include/header.hpp"


constexpr int N = 1000000;   // 50000;
constexpr int limit = 50000; // 1000000000;


using namespace helper;


int solution(std::vector<int>& A)
{
  size_t N = A.size();
  if (N == 1)
    return A[0];
  if (N == 2)
    return (A[0] > A[1] ? A[1] : A[0]);

  size_t half = (int)(N / 2);
  print<char[], int>("halfpoint", half);

  if ((A[0] > A[half])) {
    for (size_t i = 0; i < half; i++) {
      if (A[i] > A[i + 1])
        return A[i + 1];
    }
  }
  else if (A[half] > A[N - 1]) {
    for (size_t i = half; i < N - 1; i++) {
      if (A[i] > A[i + 1])
        return A[i + 1];
    }
  }
  return A[0];
} // solution


int solutionQ(std::vector<int>& A, int div)
{
  size_t N = A.size();
  if (N == 1)
    return A[0];
  if (N == 2)
    return (A[0] > A[1] ? A[1] : A[0]);

  const size_t M = std::max((int)(N / div), 1);
  //   print<char[], int>("divisor", M);

  std::vector<std::pair<int, int>> SE(div, std::pair<int, int>(0, N - 1));
  SE[0] = std::pair<int, int>(0, M);
  for (int j = 1; j < div - 1; j++) {
    SE[j] = std::pair<int, int>(SE[j - 1].second, std::min((j + 1) * M, N - 1));
  }
  SE[div - 1] = std::pair<int, int>(SE[div - 2].second, N - 1);
  //   print<char[], int>("start-ends", SE);

  for (int j = 0; j < div; j++) {
    if ((A[SE[j].first] > A[SE[j].second])) {
      auto temp =
        std::vector<int>(A.begin() + SE[j].first, A.begin() + SE[j].second);
      solutionQ(temp, 2);
      //   for (int i = SE[j].first; i < SE[j].second; i++) {
      //     if (A[i] > A[i + 1])
      //       return A[i + 1];
      //   }
    }
  }
  return A[0];
} // solution


int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(-N, N);

  std::vector<int> vector = gen.randomUniqueVector(N);
  std::sort(vector.begin(), vector.end());
  std::rotate(
    vector.begin(),
    vector.begin() + [&gen]() -> int
    {
      int rot = gen();
      while (rot < 0) {
        rot = gen();
      }
      return rot;
    }(),
    vector.end());
  int result;

  //   vector = {3, 4, 5, 1, 2};       // 1
  //   vector = {4, 5, 6, 7, 0, 1, 2}; // 0
  //   vector = {11, 13, 15, 17};      // 11
  //   vector = {11, 13, 15};          // 11
  //   print<char[], int>("vector", vector);

  Timer t;
  t.tick();
  result = solution(vector);
  t.tock();
  print<char[], int>("result", result);

  t.tick();
  result = solutionQ(vector, 2);
  t.tock();
  print<char[], int>("result", result);

  return 0;
} // main