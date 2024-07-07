#include "../include/header.hpp"


constexpr int N = 100000;    // 100000;
constexpr int limit = 10000; // 10000;


using namespace helper;


int solution(const std::vector<int>& B)
{
  std::vector<int> A(B.size());
  std::copy(B.begin(), B.end(), A.begin());
  int N = A.size();

  if (N == 1) { // If only one element, either factory with polution or forrest.
    return (-1 * std::min(0, A[0]));
  }

  int trees = 0;   // Total planted tree counter.
  int ecoDiff = 0; // Necessary eco balancing.

  // First field (manual).
  if ((A[0] + A[1]) < 0) {
    ecoDiff = std::abs(A[0] + A[1]);
    A[1] += ecoDiff;
    trees += ecoDiff;
  };

  // Last field (manual).
  if (N > 2 && (A[N - 1] + A[N - 2]) < 0) {
    ecoDiff = std::abs(A[N - 1] + A[N - 2]);
    A[N - 2] += ecoDiff;
    trees += ecoDiff;
  }

  // Iterate rest of fields, do all in-between.
  for (int i = 1; i < N - 1; ++i) {
    if (A[i - 1] + A[i] + A[i + 1] >= 0) {
      continue; // Nothing to do here, balanced.
    }

    // Ecological balance of this field.
    ecoDiff = std::abs(A[i - 1] + A[i] + A[i + 1]);
    A[i + 1] += ecoDiff; // Left part initially balanced before.
    trees += ecoDiff;    // Count.
  }

  return trees;
} // solution


int solutionB(const std::vector<int>& B)
{
  std::vector<int> A(B.size());
  std::copy(B.begin(), B.end(), A.begin());

  int N = A.size();

  if (N == 1) { // If only one element, either factory with polution or forrest.
    return (-1 * std::min(0, A[0]));
  }

  int trees = 0;   // Total planted tree counter.
  int ecoDiff = 0; // Necessary eco balancing.

  // First field (manual).
  if ((A[0] + A[1]) < 0) {
    ecoDiff = std::abs(A[0] + A[1]);
    A[1] += ecoDiff;
    trees += ecoDiff;
  };

  // Last field (manual).
  if (N > 2 && (A[N - 1] + A[N - 2]) < 0) {
    ecoDiff = std::abs(A[N - 1] + A[N - 2]);
    A[N - 2] += ecoDiff;
    trees += ecoDiff;
  }

  // Iterate rest of fields, do all in-between.
  for (int i = 1; i < N - 1; ++i) {
    if (A[i - 1] + A[i] + A[i + 1] >= 0) {
      continue; // Nothing to do here, balanced.
    }

    // Ecological balance of this field.
    ecoDiff = std::abs(A[i - 1] + A[i] + A[i + 1]);
    A[i + 1] += ecoDiff; // Left part initially balanced before.
    trees += ecoDiff;    // Count.
  }

  return trees;
} // solutionB


int solutionC(const std::vector<int>& B)
{
  std::vector<int> A(B.size());
  std::copy(B.begin(), B.end(), A.begin());

  const size_t N = A.size();

  int result = 0;
  for (size_t i = 0; i < N; i++) {
    if (A[i] < 0) {
      int min = std::numeric_limits<int>::max();
      if (i > 0) {
        min = A[i - 1];
      }
      if (i < N - 1) {
        min = std::min(min, A[i + 1]);
      }

      if (min >= 0 && min + A[i] >= 0) {
        continue;
      }
      else {
        int diff = std::abs(A[i] + min);
        result += diff;
        A[i] += diff;
      }
    }
  }

  for (size_t i = 0; i < N; i++) {
    if (A[i] >= 0) {
      int adj = 0;
      if (i > 0) {
        adj = A[i - 1];
      }
      if (i < N - 1) {
        adj += A[i + 1];
      }

      if (adj + A[i] >= 0) {
        continue;
      }
      else {
        int diff = std::abs(A[i] + adj);
        result += diff;
        A[i] += diff;
      }
    }
  }

  return result;
} // solution C


int solutionD(const std::vector<int>& B)
{
  std::vector<int> A(B.size());
  std::copy(B.begin(), B.end(), A.begin());

  const size_t N = A.size();

  A.insert(A.begin(), {0});
  A.push_back({0});

  int result = 0;
  for (size_t i = 1; i < N; i++) {
    if (A[i - 1] + A[i] + A[i + 1] < 0) {
      result += std::abs(A[i - 1] + A[i] + A[i + 1]);
      A[i + 1] += std::abs(A[i - 1] + A[i] + A[i + 1]);
    }
  }
  return result;
} // solutionD


int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(-limit, limit);

  int result = -1;
  std::vector<int> vector = gen.randomVector(1, N);

  // vector = {1, -3, 2}; // 2
  // vector = {-3, 2, 4, -5, 3}; // 3
  // vector = {-2, 1, -3, 1};    // 4

  Timer t;
  t.tick();
  result = solution(vector);
  print<char[], int>("result", result);
  t.tock();

  t.tick();
  result = solutionB(vector);
  print<char[], int>("result B", result);
  t.tock();

  t.tick();
  result = solutionC(vector);
  print<char[], int>("result C", result);
  t.tock();

  t.tick();
  result = solutionD(vector);
  print<char[], int>("result D", result);
  t.tock();

  return 0;
} // main