#include "../../include/header.hpp"


constexpr int N = 10;     // 50000;
constexpr int limit = 10; // 1000000000;


using namespace helper;


std::vector<std::vector<int>> solutionA(const std::vector<int>& B)
{
  // Two pointer solution.
  size_t N = B.size();
  if (N < 3)
    return {};

  std::vector<int> A(N);
  std::copy(B.begin(), B.end(), A.begin());

  std::sort(A.begin(), A.end());
  if (A[0] > 0)
    return {};
  print<char[], int>("sorted", A);

  std::vector<std::vector<int>> results;
  for (size_t i = 0; i < N; i++) {
    if (A[i] > 0)
      break;

    if (i > 0 && A[i] == A[i - 1])
      continue;

    int low = i + 1;
    int top = N - 1;
    while (low < top) {
      int total = A[i] + A[low] + A[top];

      if (total > 0)
        top--;
      else if (total < 0)
        low++;
      else {
        results.push_back({A[i], A[low], A[top]});
        low++;

        while ((A[top] == A[low - 1]) && (low < top)) {
          low++;
        }
      }
    }
  }
  return results;
} // solution


std::vector<std::vector<int>> solutionB(const std::vector<int>& B)
{
  // Hash map solution.
  size_t N = B.size();
  if (N < 3)
    return {};

  std::vector<int> A(N);
  std::copy(B.begin(), B.end(), A.begin());

  std::sort(A.begin(), A.end());
  if (A[0] > 0)
    return {};

  std::unordered_map<int, std::vector<int>> map;
  for (size_t i = 0; i < N; i++) {
    map[A[i]].push_back(i);
  }

  auto findTwoSum = [&map, &N, &A](const int index, size_t& j, const int sum,
                                   std::vector<int>& values) -> bool
  {
    for (size_t i = index + 1; i < N - 1; i++) {
      if (map.count(sum - A[i]) > 0) {
        if (j < map[sum - A[i]].size()) {
          std::cout << "index:" << index << ", sum:" << sum << ", i:" << i
                    << ", A[i]:" << A[i] << ", diff:" << sum - A[i]
                    << ", map.count(diff):" << map.count(sum - A[i])
                    << ", j:" << j << ", map[j]:" << map[sum - A[i]][j]
                    << ", case:" << (j < map[sum - A[i]].size() - 1)
                    << std::endl;
          if (map[sum - A[i]][j] > (int)i) {
            values.push_back(A[i]);
            values.push_back(A[map[sum - A[i]][j]]);

            print<char[], int>("triplet", values);
            j++;
            return (j < map[sum - A[i]].size() - 1);
          }
        }
      }
    }
    return false;
  };

  std::vector<std::vector<int>> results;
  std::vector<int> triplet;
  size_t count;
  for (size_t i = 0; i < N - 2; i++) {
    count = 0;
    while (findTwoSum(i, count, -A[i], triplet) || (triplet.size() == 2)) {
      triplet.push_back(A[i]);
      results.push_back(triplet);
      triplet.clear();
    }
  }
  return results;
} // solution


int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(-limit, limit);
  std::vector<int> vector = gen.randomVector(N);

  // vector = {-1, 0, 1, 2, -1, -4}; // [[-1,-1,2],[-1,0,1]]
  // vector = {0, 1, 1}; // []
  print<char[], int>("vector", vector);

  std::vector<std::vector<int>> result;
  Timer t;
  t.tick();
  result = solutionA(vector);
  t.tock();
  print<char[], int>("result", result);

  t.tick();
  result = solutionB(vector);
  t.tock();
  print<char[], int>("result", result);

  return 0;
} // main