#include "../../include/header.hpp"


constexpr int N = 10;     // 100000;
constexpr int limit = 10; // 10000;


using namespace helper;


int solution(std::vector<int>& A)
{
  int M = A.size();
  if (M == 3) {
    return 0;
  }

  int maxSlice = -1;

  if (false) {
    std::vector<int> lhsSliceSum(M, 0);
    std::vector<int> rhsSliceSum(M, 0);
    for (int i = 1; i < M - 1; i++)
      lhsSliceSum[i] = std::max(lhsSliceSum[i - 1] + A[i], 0);
    for (int i = M - 2; i > 0; i--)
      rhsSliceSum[i] = std::max(rhsSliceSum[i + 1] + A[i], 0);
    for (int i = 1; i < M - 1; i++)
      maxSlice = std::max(maxSlice, lhsSliceSum[i - 1] + rhsSliceSum[i + 1]);
  }

  auto sliceSum =
    [&A](std::vector<int>::iterator start, std::vector<int>::iterator end)
  {
    if (start == end) {
      return 0;
    }
    int sum = 0;

    for (auto i = start + 1; ((i < end) && (i != A.end())); i++) {
      sum += *i;
    }
    return sum;
  };

  int x = 0;
  int y = x + 1;
  int z = y + 1;

  for (auto Z = A.begin() + 2; Z < A.end(); Z++) {
    for (auto Y = A.begin() + 1; Y < Z; Y++) {
      for (auto X = A.begin(); X < Y; X++) {
        auto res = sliceSum(X, Y) + sliceSum(Y, Z);
        maxSlice = std::max(maxSlice, res);
        x++;
      }
      y++;
      x = 0;
    }
    z++;
    x = 0;
    y = 1;
  }
  return maxSlice;
} // solution

int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(-limit, limit);

  int result = -1;
  std::vector<int> vector = gen.randomVector(1, N);
  vector = {3, 2, 6, -1, 4, 5, -1, 2};
  print<char[], int>("vector", vector);

  Timer t;
  t.tick();
  result = solution(vector);
  t.tock();
  print<char[], int>("result", result);

  return 0;
} // main