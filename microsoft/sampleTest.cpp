
#include "../include/header.hpp"


constexpr int N = 10000;       // 10;
constexpr int limit = 1000000; // 10;


using namespace helper;


int solutionA(std::vector<int>& A)
{
  if (A.size() == 1) {
    return (A[0] < 0 ? 1 : 1);
  }
  std::sort(A.begin(), A.end(), std::less<int>());
  // print<char[], int>("sorted", A);

  if (A[0] > 1) {
    return 1;
  }

  for (size_t i = 0; i < A.size() - 1; i++) {
    if (A[i + 1] <= 1) {
      continue;
    }

    if ((A[i] < 0) && (A[i + 1] > 1)) {
      return 1;
    }

    if (std::abs(A[i + 1] - A[i]) > 1) {
      return (A[i] + 1);
    }
  }

  return (A.back() <= 0 ? 1 : A.back() + 1);
} // solution


int solutionB(std::vector<int>& A)
{
  std::sort(A.begin(), A.end(), std::less<int>());
  int result = 1;

  // Starting from 1 (min), compare all elements,
  // if it does not match that would the missing number.
  for (int i : A) {
    if (i == result) {
      result++;
    }
  }
  return result;
} // solution


int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(-limit, limit);

  std::vector<int> vector;

  // vector = {1, 2, 3}; // 4
  // vector = {-1, -3};                // 1
  // vector = {-1, -2, -4, 0, -1, -3}; // 1
  // vector = {1, 3, 6, 4, 1, 2};      // 5
  // vector = {-3, -6, 4, 5, 6};       // 1

  Timer t;
  t.tick();
  for (int j = 0; j < 100000; j++) {
    vector = gen.randomVector(1, N);
    if (solutionA(vector) != solutionB(vector)) {
      print<char[], int>("vector", vector);
      print<char[], int>("results{A:B}", std::vector<int>({solutionA(vector),
                                                           solutionB(vector)}));
      break;
    }
  }
  t.tock();

  return 0;
} // main