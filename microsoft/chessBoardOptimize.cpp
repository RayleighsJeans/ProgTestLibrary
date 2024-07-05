#include "../include/header.hpp"


constexpr int N = 10000;                                   // 100000;
constexpr int limit = std::numeric_limits<int>::max() / 2; // 10000;


constexpr bool debug = false;


using namespace helper;


int solution(std::vector<std::vector<int>>& A)
{
  if (A.empty() || A[0].empty() || A.size() < 2 || A[0].size() < 2) {
    return -1;
  }

  int N = A.size();
  int M = A[0].size();

  /// @brief Transposing a 2D vector (matrix) and producing sorted columns.
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

  /// @brief Lambda to find 1st and 2nd maxima(s) of a given vector
  /// and return a vector of pairs (their locations).
  /// @param idx Index/number of this vector.
  /// @param vector The data container to look in.
  /// @return Vector of pairs containing the locations.
  auto vectorMaxima =
    [](const int idx,
       const std::vector<int>& vector) -> std::vector<std::pair<int, int>>
  {
    if (debug)
      print<char[], int>("vector", vector);

    std::vector<std::pair<int, int>> positions;

    // First maximum and its location.
    const int maxPos = std::distance(
      vector.begin(), std::max_element(vector.begin(), vector.end()));
    positions.push_back(std::make_pair(idx, maxPos));

    // Produce second order maximum.
    std::vector<int> buffer(2);
    std::partial_sort_copy(vector.begin(), vector.end(), buffer.begin(),
                           buffer.end(), std::greater<int>());
    if (debug)
      print<char[], int>("buffer", buffer);

    for (size_t k = 0; k < vector.size(); k++) {
      if ((k != (size_t)maxPos) && (vector[k] == buffer[1])) {
        positions.push_back(std::make_pair(idx, k));
      }
    }

    if (debug)
      print<char[], int>("positions", positions);
    return positions;
  }; // vectorMaxima

  std::vector<std::vector<std::pair<int, int>>> rowMaxes(
    N, std::vector<std::pair<int, int>>());
  std::vector<std::vector<std::pair<int, int>>> columnMaxes(
    M, std::vector<std::pair<int, int>>());

  // Final result designations.
  int result = -1;
  std::vector<std::pair<int, int>> rookPositions(2, std::pair<int, int>());

  // Iterate through the rows and all columns at the same time once.
  // Then immediately stark looking for ideal positions where the rooks
  // can't strike each other.
  for (int i = 0; i < N; i++) {
    rowMaxes[i] = vectorMaxima(i, A[i]);

    if (i == 0) {
      for (int j = 0; j < M; j++) {
        columnMaxes[j] = vectorMaxima(j, columns[j]);
      }
    }

    for (auto& rowPair : rowMaxes[i]) {
      for (int m = 0; m < M; m++) {
        for (auto& colPair : columnMaxes[m]) {

          // Attention: column indices are reversed due to the transposed
          // nature of the columns container from above.
          if ((rowPair.first != colPair.second) &&
              (rowPair.second != colPair.first)) {
            if (A[rowPair.first][rowPair.second] +
                  A[colPair.second][colPair.first] >
                result) {
              result = A[rowPair.first][rowPair.second] +
                       A[colPair.second][colPair.first];

              // Store this position:
              // First rook,
              rookPositions[0] = std::make_pair(rowPair.first, rowPair.second);
              // and second rook.
              rookPositions[1] = std::make_pair(colPair.second, colPair.first);
            }
          }
        }
      }
    }
  }

  print<char[], int, int>("positions", rookPositions);
  return result;
} // solution

int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(1, limit);

  int result = -1;
  std::vector<std::vector<int>> vector = gen.random2dVector(2, N, 2, N);
  std::vector<size_t> sizes = {vector.size(), vector[0].size()};
  print<char[], size_t>("sizes", sizes);

  // vector = {{12, 1}, {1, 12}}; // 24
  // vector = {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}}; // 5
  // vector = {{5, 5, 5, 1}, {5, 1, 1, 1}, {5, 5, 10, 10}, {1, 1, 1, 5}}; // 15

  Timer t;
  t.tick();
  result = solution(vector);
  t.tock();
  print<char[], int>("result", result);

  return 0;
} // main