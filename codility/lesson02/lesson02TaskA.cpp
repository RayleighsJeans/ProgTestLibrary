#include "../../include/header.hpp"


constexpr int N = 10;
constexpr int limit = 1000; // std::numeric_limits<int>::max();


using namespace helper;


std::vector<int> solution(std::vector<int>& A, int K)
{
  if ((A.empty()) || !K)
    return A;
  while (K) {
    A.insert(A.begin(), A.back());
    A.pop_back();
    K--;
  }
  return A;
} // solution


int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(-limit, limit);
  RandomGenerator<int> genB(0, N);

  int K;
  std::vector<int> vector;
  std::vector<int> result;
  for (int i = 0; i < 10; i++) {
    vector = gen.randomVector(0, 10);
    print<char[], int>("vector", vector);
    K = genB();

    std::cout << ">> rotate " << K << " times ..." << std::endl;
    result = solution(vector, K);
    print<char[], int>("result", result);

    file(vector);
    file(K);
    file(result);
    file.flush();
  }

  return 0;
} // main
