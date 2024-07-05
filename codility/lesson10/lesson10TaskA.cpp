#include "../../include/header.hpp"


constexpr int N = 10;     // 100000;
constexpr int limit = 10; // 10000;


using namespace helper;


int solution(int N)
{
  int i = 1;
  int counter = 0;

  auto root = sqrt(N);

  // while (i * i < N) {
  while (i < root) {
    if (N % i == 0)
      counter += 2;
    i++;
  }
  // if (i * i == N)
  if (i == root)
    counter++;

  return counter;
} // solution

int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(-limit, limit);

  int result = -1;
  int number = gen();
  number = 24; // 8
  number = std::numeric_limits<int>::max();
  print<char[], int>("number", number);

  Timer t;
  t.tick();
  result = solution(number);
  t.tock();
  print<char[], int>("result", result);

  return 0;
} // main