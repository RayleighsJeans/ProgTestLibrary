
#include "../../include/header.hpp"


constexpr int N = 100000;
constexpr int limit = std::numeric_limits<int>::max();


using namespace helper;


int solution(std::vector<int>& H)
{
  int blocks = 0;

  std::vector<int> starts;
  std::vector<int> heights;
  std::vector<int> widths;

  std::vector<int> stack;

  stack.push_back(H[0]);
  starts.push_back(0);

  for (size_t i = 0; i < H.size(); i++) {
    while (H[i] < stack.back()) {
      blocks++;

      heights.push_back(stack.back());
      widths.push_back(i - starts.back());

      stack.pop_back();
      starts.pop_back();
    }

    if (H[i] > stack.back()) {
      stack.push_back(H[i]);
      starts.push_back(i);
    }
  }

  for (size_t i = 0; i < stack.size(); i++) {
    heights.push_back(stack[i]);
    widths.push_back(H.size() - starts[i]);
  }

  print<char[], int>("heights", heights);
  print<char[], int>("widths", widths);

  return blocks + stack.size();
} // solution


int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(1, limit);

  int result = -1;

  std::vector<int> vector = gen.randomVector(N);
  // vector = {8, 8, 5, 7, 9, 8, 7, 4, 8}; // 7
  // vector = {8, 8, 5, 7, 9, 9, 7, 4, 8}; // 6
  // vector = {8, 8, 5, 7, 9, 8, 7, 4, 8, 4}; // 7

  Timer t;
  t.tick();
  result = solution(vector);
  t.tock();
  print<char[], int>("result", result);

  return 0;
} // main