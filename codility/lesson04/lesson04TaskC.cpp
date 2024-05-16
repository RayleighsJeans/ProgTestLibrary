#include "../../include/header.hpp"


constexpr int N = 10;     // 100000;
constexpr int limit = 10; // std::numeric_limits<int>::max();


using namespace helper;


std::vector<int> solution(int M, std::vector<int>& A)
{
  std::vector<int> counters(M, 0);
  int oldMax = 0;
  int counterMax = 0;

  auto increase = [&counters, &counterMax](const int x)
  {
    counters[x] += 1;
    counterMax = std::max(counterMax, counters[x]);
  };

  auto maxCounter = [&counters, &counterMax, &oldMax]()
  {
    if (oldMax == counterMax)
      return;
    std::fill(counters.begin(), counters.end(), counterMax);
    oldMax = counterMax;
  };

  for (size_t i = 0; i < A.size(); i++) {
    if ((1 <= A[i]) && (A[i] <= M)) {
      increase(A[i] - 1);
    }
    else if (A[i] == M + 1) {
      maxCounter();
    }
  }
  return counters;
} // solution


int main()
{
  WriteToFile<int> file(__FILE__);

  RandomGenerator<int> genA(1, N);

  int M = -1;

  std::vector<int> result;
  std::vector<int> vector;

  Timer t;
  t.tick();
  for (int i = 0; i < 10; i++) {
    int M = genA();


    RandomGenerator<int> genB(1, M + 1);
    vector = genB.randomVector(M);

    file(vector);
    print("vector", vector);
    result = solution(M, vector);
    print("result", result);
    file(result);
    file.flush();
  }
  t.tock();

  return 0;
} // main