
#include "../../include/header.hpp"


constexpr int N = 10;     // 100000
constexpr int limit = 10; // std::numeric_limits<int>::max


using namespace helper;


int solution(std::vector<int>& H)
{
  int blocks = 1;

  int height = -1;
  for (size_t i = 0; i < H.size(); i++) {}


  return blocks;
} // solution


int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(1, limit);

  int result = -1;

  std::vector<int> vector = gen.randomVector(N);

  Timer t;
  t.tick();
  result = solution(vector);
  t.tock();
  print<char[], int>("result", result);

  return 0;
} // main