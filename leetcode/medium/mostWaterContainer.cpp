#include "../../include/header.hpp"


constexpr int N = 10;     // 50000;
constexpr int limit = 10; // 1000000000;


using namespace helper;


int solution(std::vector<int>& H)
{
  std::vector<int>::iterator A, B;
  auto left = H.begin();
  auto right = H.end() - 1;

  int i, j;

  int N;
  int volume = -1;
  while (left != right) {

    i = std::distance(H.begin(), left);
    j = std::distance(H.begin(), right);

    N = std::distance(left, right);
    if (std::min(*left, *right) * N > volume) {
      A = left;
      B = right;
      volume = std::min(*left, *right) * N;
    }

    print<char[], int>("data", {i, j, N, *left, *right, volume});

    if (*left < *right) {
      left++;
    }
    else {
      right--;
    }
  }

  return volume;
} // solution


int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(-limit, limit);

  std::vector<int> vector = gen.randomVector(N);
  int result;

  vector = {1, 8, 6, 2, 5, 4, 8, 3, 7}; // 49
  // vector = {1, 1}; // 1
  print<char[], int>("vector", vector);

  Timer t;
  t.tick();
  result = solution(vector);
  t.tock();
  print<char[], int>("result", result);

  return 0;
} // main