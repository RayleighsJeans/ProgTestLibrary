#include "../../include/header.hpp"


constexpr int N = 10;     // 50000;
constexpr int limit = 10; // 1000000000;


using namespace helper;


std::vector<std::vector<int>> solutionA(std::vector<int>& A)
{
  std::vector<std::vector<int>> results;
  return results;
  // two pointer solution
} // solution


std::vector<std::vector<int>> solutionB(std::vector<int>& A)
{
  // hash map solution
  size_t N = A.size();
  std::sort(A.begin(), A.end());

  std::unordered_map<int, std::vector<int>> map;
  for (size_t i = 0; i < N; i++) {
    map[A[i]].push_back(i);
  }
  for (auto& [key, value] : map)
    print<int, int>(key, value);

  auto findTwoSum = [&map, &N, &A](const int index, const int sum,
                                   std::vector<int>& values) -> bool
  {
    for (size_t i = 0; i < N; i++) {
      if (i != index) {
        if (map.count(sum - A[i]) > 0) {
          for (auto& j : map[sum - A[i]]) {
            std::cout << index << ", " << sum << ", " << i << ", " << A[i]
                      << ", " << sum - A[i] << ", " << map.count(sum - A[i])
                      << ", " << j << std::endl;

            if (j != index) {
              values.push_back(A[i]);
              values.push_back(A[j]);
              return true;
            }
          }
        }
      }
    }
    return false;
  };

  std::vector<std::vector<int>> results;
  std::vector<int> triplet;
  for (size_t i = 0; i < N; i++) {
    triplet.push_back(A[i]);
    if (findTwoSum(i, -A[i], triplet)) {
      print<char[], int>("triplet", triplet);
      results.push_back(triplet);
    }
    triplet.clear();
  }

  return results;
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
  // t.tick();
  // auto result = solutionA(vector);
  // t.tock();
  // print<char[], int>("result", result);

  t.tick();
  auto result = solutionB(vector);
  t.tock();
  print<char[], int>("result", result);

  return 0;
} // main