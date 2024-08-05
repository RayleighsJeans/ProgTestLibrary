#include "../../include/implementation/graphImpl.hpp"
#include "../../include/implementation/treeImpl.hpp"


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

  std::vector<std::vector<int>> results;

  for (size_t i = 0; i < N - 2; i++) {
    if (A[i] > 0)
      break;

    for (size_t k = i + 1; k < N - 1; k++) {
      if (map.count(-A[i] - A[k]) > 0) {
        auto diff = -A[i] - A[k];
        auto suffix = map[diff].back();

        if ((suffix > (int)i) && (suffix > (int)k)) {
          if (((i > 0) && (A[i] == A[i - 1])) ||
              ((k > 0) && (k > i + 1) && (A[k] == A[k - 1])))
            continue;

          results.push_back({A[i], A[k], diff});
          print<char[], int>("triplet", {A[i], A[k], diff});
        }
      }
      k = map[A[k]].back();
    }
    i = map[A[i]].back();
  }

  return results;
} // solution


int main()
{
  if (false) {
    WriteToFile<int> file(__FILE__);
    RandomGenerator<int> gen(-limit, limit);
    std::vector<int> vector = gen.randomVector(N);

    vector = {-1, 0, 1, 2, -1, -4};
    vector = {0, 1, 1};
    vector = {0, 3, 5, 1, 1, -6, 7, 2, -1, -3};
    vector = {-10, -9, -8, -8, -2, 1, 1, 8, 9, 10};
    vector = std::vector<int>(1000, 0);

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
  }


  return 0;
} // main