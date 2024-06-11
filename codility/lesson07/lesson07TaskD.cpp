
#include "../../include/header.hpp"


constexpr int N = 10; // 100000


using namespace helper;


int solution(std::string& S)
{
  return 1;
} // solution


int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(0, 1);
  RandomGenerator<int> genB(0, 1);

  int result = -1;

  Timer t;
  t.tick();
  // result = solution();
  t.tock();
  print<char[], int>("result", result);

  return 0;
} // main