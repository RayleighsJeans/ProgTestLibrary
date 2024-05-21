#include "../../include/header.hpp"


constexpr int N = 10;     // 200000
constexpr int limit = 10; // std::numeric_limits<int>::max();


using namespace helper;


int solution(std::vector<int>& A, std::vector<int>& B) {}


int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(0, 2);


  int result = -1;
  Timer t;
  t.tick();
  result = solution();
  t.tock();
  print("result", result);

  return 0;
}