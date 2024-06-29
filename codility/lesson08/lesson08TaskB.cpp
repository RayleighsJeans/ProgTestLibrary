#include "../../include/header.hpp"


constexpr int N = 11;
constexpr int limit = 10;


using namespace helper;


int solution(std::vector<int>& A)
{
  std::vector<int> stack;
  std::vector<int> positions;

  size_t M = A.size();
  for (size_t i = 0; i < M; i++) {
    int a = A[i];

    if (stack.size() == 0) {
      stack.push_back(a);
    }
    else if (a != stack.back()) {
      stack.pop_back();
    }
    else {
      stack.push_back(a);
    }
  }

  // Count.
  int count = 0;
  for (size_t i = 0; i < M; i++) {
    if (A[i] == stack.back()) {
      count++;
      positions.push_back(i);
    }
  }

  print<char[], int>("count", count);
  print<char[], int>("positions", positions);

  // Has leader?
  if (count > (A.size() / (float)2)) {
    const int leader = stack.back();
    count = 0;

    size_t N = positions.size();

    int leftCount = 0;
    int rightCount = N;

    positions.clear();
    for (size_t j = 0; j < M; j++) {
      if (A[j] == leader) {
        leftCount++;
        rightCount--;
      }

      std::cout << j << " -- count " << count << std::endl;
      print<int, float>(leftCount, (j + 1) / (float)2);
      print<int, float>(rightCount, (M - j - 1) / (float)2);

      if ((leftCount > ((j + 1) / (float)2)) &&
          (rightCount > ((M - j - 1) / (float)2))) {
        count++;
        positions.push_back(j);
      }
    }

    print<char[], int>("equis", positions);
    return count;
  }
  else {
    return 0;
  }
} // solution


int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(-limit, limit);

  int result = -1;
  std::vector<int> vector = gen.randomLeaderVector(N);

  // vector = {4, 6, 6, 6, 6, 8, 8}; // 6 -- -- 0
  // vector = {3, 4, 3, 2, 3, -1, 3, 3}; // 3 -- 0, 2, 4, 6 -- 4
  vector = {1, 2, 1}; // 1 -- -- 0
  // vector = {2, 1, 1, 3, 4}; // -1 -- -- 0
  // vector = {4, 3, 4, 4, 4, 2}; // 4 -- 0, 2 -- 2

  print<char[], int>("vector", vector);

  Timer t;
  t.tick();
  result = solution(vector);
  t.tock();
  print<char[], int>("result", result);

  return 0;
} // main