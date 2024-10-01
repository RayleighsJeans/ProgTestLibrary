#include "../include/header.hpp"


#if 0
constexpr int N = 100;    // 50000;
constexpr int limit = 10; // 1000000000;
#else
constexpr int N = 50000;
constexpr int limit = 1000000000;
#endif


using namespace helper;


// you can use includes, for example:
#include <algorithm>
#include <map>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

std::vector<int> solution(std::vector<int>& A)
{
  const size_t N = A.size();

  // New skyline.
  std::vector<int> skyline(N, 0);

  // Could do greedy algorithm with sorting A, however
  // for comprehensibility (i.e. human readability)
  // use map and remember the skyline.

  // Map containing existing building(s) heights.
  std::map<int, bool> cityPlan;

  // New in-place block to build if bad height.
  int newBlock = -1;
  for (size_t i = 0; i < N; i++) {

    // If already have SC at this level, change height.
    if (cityPlan.count(A[i])) {
      newBlock = (A[i] - 1 > 0 ? A[i] - 1 : 1);

      while (cityPlan.count(newBlock) && (newBlock > 1)) {
        newBlock--;
      }
      // TODO: Here could check for 1/-1 height, or change while,
      // though reiterating with i = 0 through the new skyline
      // can possibility loop infinitely for ill posed inputs.
      skyline[i] = newBlock;
      cityPlan[newBlock] = true; // Remember new SC height!
    }
    else {
      // This SC is just fine.
      cityPlan[A[i]] = true;
      skyline[i] = A[i];
    }
  }

  return skyline;
} // solution


std::vector<int> solutionB(std::vector<int>& A)
{
  // This is a greedy version of the above problem.
  // Runs minutely faster (locally), however changes the layout of the
  // input skyline entirely due to sorting.

  const size_t N = A.size();
  std::vector<int> skyline(N, 0);

  // Sort array A in descending order
  std::sort(A.begin(), A.end(), std::greater<int>());

  // Assign heights to skyscrapers
  int block = A[0];
  for (size_t i = 0; i < N; i++) {
    skyline[i] = block;
    block = std::max(1, std::min(block - 1, A[i + 1]));
  }

  return skyline;
} // solutionB


int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(1, limit);

  std::vector<int> vector = gen.randomVector(N);
  std::vector<int> result(vector.size(), -1);

  // vector = {1, 2, 3};       // {1, 2, 3} // 6
  // vector = {9, 4, 3, 7, 7}; // {9, 4, 3, 7, 6} // 29
  // vector = {2, 5, 4, 5, 5}; // {1, 2, 3, 4, 5} // 15
  // vector = {3, 3, 3, 4};    // {1, 2, 3, 4} // 10
  // vector = {2, 2, 2};       // {0, 1, 2} // 10

  auto allPositive = [](const std::vector<int>& vector)
  {
    return ((int)vector.size() == std::count_if(vector.begin(), vector.end(),
                                                [](int c) { return c > 0; }));
  };

  // print<char[], int>("vector", vector);
  Timer t;
  t.tick();
  result = solution(vector);
  t.tock();
  print<char[], bool>("pos def", allPositive(result));
  print<char[], int>("height", std::reduce(result.begin(), result.end()));

  t.tick();
  result = solutionB(vector);
  t.tock();
  print<char[], bool>("pos defB", allPositive(result));
  print<char[], int>("heightB", std::reduce(result.begin(), result.end()));

  return 0;
} // main