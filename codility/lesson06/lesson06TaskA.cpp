#include "../../include/header.hpp"


using namespace helper;


constexpr int N = 100000;      // 100000
constexpr int limit = 1000000; // std::numeric_limits<int>::max();


int solution(std::vector<int>& A)
{
  std::vector<int> B(A);

  std::sort(B.begin(), B.end());
  B.erase(std::unique(B.begin(), B.end()), B.end());
  return B.size();
} // solution

int solutionB(std::vector<int>& A)
{
  std::vector<int> B(A);

  std::map<int, int> map;
  for (auto& b : B) {
    map[b] += 1;
  }

  std::vector<int> keys;
  for (auto& [key, value] : map)
    if (value > 1)
      keys.push_back(key);
  for (auto& key : keys)
    map.erase(key);

  return map.size();
} // solutionB


int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(-limit, limit);

  int result = -1;
  std::vector<int> vector;

  //   vector = {2, 1, 1, 2, 3, 1};

  Timer t;

  t.tick();
  for (int i = 0; i < 100; i++) {
    vector = gen.randomVector(0, N);
    print<char[], int>("vector", vector);
    result = solution(vector);
    print<char[], int>("result", result);
  }
  t.tock();

  t.tick();
  for (int i = 0; i < 100; i++) {
    vector = gen.randomVector(0, N);
    print<char[], int>("vector", vector);
    result = solutionB(vector);
    print<char[], int>("result", result);
  }
  t.tock();

  return 0;
}