#include "../../include/header.hpp"


constexpr int N = 10;


using namespace helper;


int solution(int X, std::vector<int>& A)
{
  std::vector<bool> map(X + 1, false);
  map[0] = true;

  auto allLeaves = [&map]()
  {
    return std::all_of(map.begin(), map.end(), [](bool v) { return v; });
  };

  for (size_t i = 0; i < A.size(); i++) {
    if (map[A[i]])
      continue;
    map[A[i]] = true;
    if (allLeaves())
      return i;
  }
  return -1;
} // solution


int solutionB(int X, std::vector<int>& A)
{
  std::map<int, bool> map;

  for (size_t i = 0; i < A.size(); i++) {
    if (map[A[i]])
      continue;
    map[A[i]] = true;
    if ((int)map.size() == X)
      return i;
  }
  return -1;
} // solution


int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(1, N);

  std::vector<int> vector;
  int X = -1;
  int M = -1;

  int result = -1;

  Timer t;
  t.tick();
  for (int i = 0; i < 10; i++) {
    X = gen();
    while (M < X)
      M = gen();

    RandomGenerator<int> genB(1, X);
    vector = genB.randomVector(M);
    print<char[], int>("frog goes to", X);
    print<char[], int>("vector", vector);

    result = solution(X, vector);
    print<char[], int>("frog went at ", result);
  }
  t.tock();

  return 0;
} // main
