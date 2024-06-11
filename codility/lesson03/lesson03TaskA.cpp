#include "../../include/header.hpp"


constexpr int N = 10;
constexpr int limit = 10; // std::numeric_limits<int>::max();


using namespace helper;


int solution(int X, int Y, int D)
{
  if (X >= Y)
    return 0;
  int rem = (Y - X) % D;
  int div = (Y - X > D) ? (int)((Y - X) / D) : 0;
  return (div + (rem == 0 ? 0 : 1));
} // solution


int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(1, limit);

  std::vector<int> results;
  for (int i = 0; i < 10; i++) {
    int x = gen();
    int y = gen();
    results.push_back(x);
    results.push_back(y);

    while (y < x) {
      y = gen();
    }
    int D = gen();
    results.push_back(D);

    results.push_back(std::div(y - x, D).quot);
    results.push_back(std::div(y - x, D).rem);

    std::cout << ">> For X=" << x << ", Y=" << y << ", D=" << D;
    std::cout << ", quot=" << std::div(y - x, D).quot
              << ", rem=" << std::div(y - x, D).rem;
    std::cout << ", res=" << solution(x, y, D) << std::endl;

    file(results);
    file(solution(x, y, D));
    file.flush();

    results.clear();
  }

  return 0;
} // main
