#include "../../include/header.hpp"


constexpr int N = 10000;       // 10;
constexpr int limit = 1000000; // 10;


using namespace helper;


std::vector<int> solutionA(const std::vector<int>& B, const int& target)
{
  size_t N = B.size();
  std::vector<int> A(N);
  std::copy(B.begin(), B.end(), A.begin());

  std::vector<size_t> indices(N);
  std::iota(indices.begin(), indices.end(), 0);
  std::stable_sort(indices.begin(), indices.end(),
                   [&A](size_t i, size_t j) { return A[i] < A[j]; });

  std::sort(A.begin(), A.end());
  for (size_t i = 0; i < N - 1; i++) {
    if (A[i] < target) {
      for (size_t j = i + 1; j < N; j++) {
        if (A[i] + A[j] <= target) {
          if (A[i] + A[j] == target) {
            return std::vector<int>({(int)indices[i], (int)indices[j]});
          }
        }
        else {
          break;
        }
      }
    }
    else {
      break;
    }
  }
  return std::vector<int>({-1});
} // solutionA


std::vector<int> solutionB(const std::vector<int>& B, const int& target)
{
  size_t N = B.size();
  std::vector<int> A(N);
  std::copy(B.begin(), B.end(), A.begin());

  std::unordered_map<int, int> numMap;
  int n = A.size();

  for (int i = 0; i < n; i++) {
    int complement = target - A[i];
    if (numMap.count(complement)) {
      return {numMap[complement], i};
    }
    numMap[A[i]] = i;
  }

  return {}; // No solution found
} // solutionB


int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(0, limit);

  std::vector<int> vector;
  int target = 0;
  std::vector<int> result;

  Timer t;
  for (int j = 0; j < 1; j++) {

    vector = gen.randomUniqueVector(N);
    {
      RandomGenerator<int> genTarget(0, vector.size() - 1);
      target += vector[genTarget()];

      int i = genTarget();
      while (vector[i] == target) {
        i = genTarget();
      }
      target += vector[i];
    }
    print<char[], int>("vector", vector);
    print<char[], int>("target", target);

    t.tick();
    result = solutionA(vector, target);
    print<char[], int>("result A", result);
    print<char[], int>("check A", vector[result[0]] + vector[result[1]]);
    t.tock();

    t.tick();
    result = solutionB(vector, target);
    print<char[], int>("result B", result);
    print<char[], int>("check B", vector[result[0]] + vector[result[1]]);
    t.tock();
  }

  return 0;
} // main