#include "../../include/header.hpp"


constexpr int N = 10;     // 50000;
constexpr int limit = 10; // 1000000000;


using namespace helper;


std::vector<std::vector<int>> solutionA(std::vector<int>& A)
{
  // two pointer solution
} // solution


std::vector<std::vector<int>> solutionB(std::vector<int>& A)
{
  // hash map solution
  size_t N = A.size();
  std::sort(A.begin(), A.end());

  std::unordered_map<int, int> map;
  for (size_t i = 0; i < N; i++) {
    map[A[i]] = i;
  }


} // solution


int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(-limit, limit);
  std::vector<int> vector = gen.randomVector(N);

  vector = {-1, 0, 1, 2, -1, -4}; // [[-1,-1,2],[-1,0,1]]
  // vector = {0, 1, 1}; // []
  print<char[], int>("vector", vector);

  Timer t;
  t.tick();
  auto result = solutionA(vector);
  t.tock();
  print<char[], int>("result", result);

  t.tick();
  auto result = solutionA(vector);
  t.tock();
  print<char[], int>("result", result);

  return 0;
} // main