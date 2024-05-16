#include "../../include/header.hpp"


constexpr int N = 10;     // 100000;
constexpr int limit = 10; // 1000000;


using namespace helper;


int solution(std::vector<int>& A)
{
  int pairs = 0;

  int eastCars = 0;
  int westCars = 0;
  for (auto& car : A) {
    if (!car)
      eastCars += 1;
    if (car) {
      westCars += 1;
      pairs += eastCars;
    }
    if (pairs > 1000000000)
      return -1;
  }
  return pairs;
} // solution


int main()
{
  WriteToFile<int> file(__FILE__);

  RandomGenerator<int> gen(0, 1);

  int result = -1;
  std::vector<int> vector;

  Timer t;
  t.tick();
  for (int i = 0; i < 10; i++) {
    vector = gen.randomVector(1, N);
    file(vector);
    print("vector", vector);
    result = solution(vector);
    print("result", result);
    file(result);
    file.flush();
  }
  t.tock();

  return 0;
} // main