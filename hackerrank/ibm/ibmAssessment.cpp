#include "../include/header.hpp"


constexpr int N = 10;     // 100000;
constexpr int limit = 10; // 10000;


using namespace helper;


int minimizeCost(std::vector<int>& arr)
{
  // Sorting for inherent structure of lowest cost.
  std::sort(arr.begin(), arr.end());
  print<char[], int>("array", arr);

  size_t N = arr.size();

  // Total cost.
  int result = 0;

  int M = 0;

  // Suppressing pedantic warnings; implicit comparison.
  size_t i = 0;
  int j = 0;

  // Lambda for selecting two fitting parts for lowest sum.
  auto nextElement = [&]()
  {
    if ((j == M) || ((i < N) && (arr[i] < arr[j]))) {
      return arr[i++];
    }
    return arr[j++];
  };

  int x, y;
  while ((N - i) + (M - j) > 1) {
    x = nextElement();
    y = nextElement();
    result += x + y;

    // Results can be stored in original array
    // and continuously worked with to safe space.
    arr[M++] = x + y;
    print<char[], int>("array", arr);
  }
  return result;
}

int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(-limit, limit);

  int result = -1;
  std::vector<int> vector = gen.randomVector(1, N);

  vector = {25, 10, 20}; // 85
  // vector = {30, 10, 20}; // 90

  print<char[], int>("vector", vector);

  Timer t;
  t.tick();

  // Test here.
  result = minimizeCost(vector);

  t.tock();
  print<char[], int>("result", result);

  return 0;
} // main