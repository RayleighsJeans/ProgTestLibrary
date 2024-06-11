#include "../../include/header.hpp"


using namespace helper;


constexpr int N = 10;     // 100000
constexpr int limit = 10; // std::numeric_limits<int>::max();


int solution(std::vector<int>& A)
{
  int result = 0;
  double minSliceAvg = (A[1] + A[0]) / 2;

  std::vector<int> prefixSum(A.size() + 1, 0);
  for (size_t i = 0; i < A.size(); i++)
    prefixSum[i + 1] = prefixSum[i] + A[i];

  double sliceAvg = minSliceAvg;
  for (size_t j = 0; j < A.size() - 1; j++) {
    if (j < A.size() - 2) {
      sliceAvg = std::min((prefixSum[j + 2] - prefixSum[j]) / 2.,
                          (prefixSum[j + 3] - prefixSum[j]) / 3.);
    }
    else {
      sliceAvg = (prefixSum[j + 2] - prefixSum[j]) / 2.;
    }


    if (sliceAvg < minSliceAvg) {
      minSliceAvg = sliceAvg;
      result = j;
    }
  }
  return result;
} // solution


int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(-limit, limit);

  int result = -1;
  std::vector<int> vector;

  for (int i = 0; i < 10; i++) {
    // vector = {4, 2, 2, 5, 1, 5, 8};
    // vector = {-18, 65, -11, 73, -22, 90, 21, 10, 47, 87};
    // vector = {1000, -1000};
    // vector = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    vector = gen.randomVector(2, N);

    file(vector);
    print<char[], int>("vector", vector);
    result = solution(vector);
    print<char[], int>("result", result);
    file(result);
    file.flush();
  }

  return 0;
} // main
