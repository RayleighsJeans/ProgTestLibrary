#include "../../include/header.hpp"


constexpr int N = 10;     // 200000
constexpr int limit = 10; // std::numeric_limits<int>::max();


using namespace helper;


int solution(std::vector<int>& A, std::vector<int>& B) {

  return -1;
}


int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(0, N);

  std::vector<int> A;
  std::vector<int> B;

  const int M = gen();
  A = gen.randomVectorN(M);
  B = gen.randomVectorN(M);

  int result = -1;
  Timer t;
  t.tick();
  result = solution(A, B);
  t.tock();
  print("result", result);

  return 0;
}