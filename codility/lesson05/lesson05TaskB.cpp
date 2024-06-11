#include "../../include/header.hpp"


constexpr int limit = 2000000000; // 2000000000;


using namespace helper;


int solution(int A, int B, int K)
{
  return ((B / K) - (A / K) + !(A % K));
} // solution


int main()
{
  WriteToFile<int> file(__FILE__);

  RandomGenerator<int> gen(0, limit);
  RandomGenerator<int> genB(1, limit);

  int result = -1;
  int A = -1;
  int B = -1;
  int K = -1;

  Timer t;
  t.tick();
  for (int i = 0; i < 1; i++) {
    A = gen();
    while (B < A)
      B = gen();
    K = genB();

    print<char[], int>("A, B, K", std::vector<int>{A, B, K});
    result = solution(A, B, K);
    print<char[], int>("result", result);

    // file(result);
    // file.flush();
  }
  t.tock();

  return 0;
} // main