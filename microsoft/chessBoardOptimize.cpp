#include "../include/header.hpp"


constexpr int N = 10;     // 100000;
constexpr int limit = 10; // 10000;

constexpr bool debug = true;


using namespace helper;


int solution(std::vector<std::vector<int>>& A)
{
  if (A.empty() || A[0].empty() || A.size() < 2 || A[0].size() < 2) {
    return -1;
  }

  int N = A.size();
  int M = A[0].size();

  std::vector<std::vector<int>> columns(M, std::vector<int>(N));
  [&A, &N, &M, &columns]() -> void
  {
    for (int m = 0; m < M; m++) {
      for (int n = 0; n < N; n++) {
        columns[m][n] = A[n][m];
      }
    }
  }();
  if (debug)
    print<char[], int>("transposed", columns);

  auto vectorMaxima = [](const std::vector<int>& vector) -> std::vector<int>
  {
    if (debug)
      print<char[], int>("vector", vector);

    std::vector<int> positions;

    std::vector<int> buffer(2);
    std::partial_sort_copy(vector.begin(), vector.end(), buffer.begin(),
                           buffer.end(), std::greater<int>());
    if (debug)
      print<char[], int>("buffer", buffer);

    const int maxPos = std::distance(
      vector.begin(), std::max_element(vector.begin(), vector.end()));
    positions.push_back(maxPos);

    for (size_t k = 0; k < vector.size(); k++) {
      if ((k != (size_t)maxPos) && (vector[k] == buffer[1])) {
        positions.push_back(k);
      }
    }
    return positions;
  }; // vectorMaxima

  std::vector<std::vector<int>> rowMaxes(N, std::vector<int>());
  std::vector<std::vector<int>> columnMaxes(M, std::vector<int>());

  int result = -1;
  std::vector<std::pair<int, int>> rookPositions;
  for (int i = 0; i < N; i++) {
    rowMaxes[i] = vectorMaxima(A[i]);
    if (debug)
      print<char[], int>("row maxes", rowMaxes[i]);

    if (i == 0) {
      for (int j = 0; j < M; j++) {
        columnMaxes[j] = vectorMaxima(columns[j]);
        if (debug)
          print<char[], int>("column maxes", columnMaxes[j]);
      }
    }

    for
  }

  return -1;
} // solution

int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(-limit, limit);

  int result = -1;
  std::vector<std::vector<int>> vector = gen.random2dVector(N, N);

  // vector = {{12, 1}, {1, 12}};                // 24
  // vector = {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}}; // 6
  vector = {{5, 5, 5, 1}, {5, 1, 1, 1}, {5, 5, 10, 10}, {1, 1, 1, 5}}; // 15
  print<char[], int>("vector", vector);

  Timer t;
  t.tick();
  result = solution(vector);
  t.tock();
  print<char[], int>("result", result);

  return 0;
} // main