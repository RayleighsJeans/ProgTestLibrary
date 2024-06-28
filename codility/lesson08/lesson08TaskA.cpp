#include "../../include/header.hpp"


constexpr int N = 11;
constexpr int limit = 10;


using namespace helper;


int solution(std::vector<int>& A)
{
  int candidate = -1;
  std::vector<int> stack;

  for (size_t i = 0; i < A.size(); i++) {
    int a = A[i];
    // print<char[], int>("candidate", candidate);
    // print<char[], int>("stack", stack);

    if (stack.size() == 0) {
      stack.push_back(a);
      candidate = i;
    }
    else if (a != stack.back()) {
      stack.pop_back();
    }
    else {
      stack.push_back(a);
    }
    // print<int, int>(a, stack);
  }

  // Count.
  int count = 0;
  for (auto& a : A) {
    if (a == stack.back()) {
      count++;
    }
  }
  // print<char[], int>("leader", stack.back());
  return (count > (A.size() / (float)2) ? candidate : -1);
} // solution


int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(-limit, limit);

  int result = -1;
  std::vector<int> vector = gen.randomLeaderVector(N);
  print<char[], int>("vector", vector);

  // vector = {4, 6, 6, 6, 6, 8, 8};
  // vector = {3, 4, 3, 2, 3, -1, 3, 3};
  // vector = {1, 2, 1};
  // vector = {2, 1, 1, 3, 4};

  Timer t;
  t.tick();
  result = solution(vector);
  t.tock();
  print<char[], int>("result", result);

  return 0;
} // main