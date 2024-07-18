#include "../../include/header.hpp"


constexpr int N = 10;     // 50000;
constexpr int limit = 10; // 1000000000;


using namespace helper;

int sgn(const int x)
{
  return (x > 0) ? 1 : ((x < 0) ? -1 : 1);
}


int solutionQ(const std::vector<int>& A, const int target, const int div)
{
  print<char[], int>("in", A);

  size_t N = A.size();
  if (N == 1)
    return (A[0] == target ? 0 : -1);
  if (N == 2)
    return ((A[0] == target) ? 0 : (A[1] == target) ? 1 : -1);

  const size_t M = std::max((int)(N / div), 1);

  std::vector<std::pair<int, int>> SE(div, std::pair<int, int>(0, N - 1));
  SE[0] = std::pair<int, int>(0, M);
  for (int j = 1; j < div - 1; j++) {
    SE[j] = std::pair<int, int>(SE[j - 1].second, std::min((j + 1) * M, N - 1));
  }
  SE[div - 1] = std::pair<int, int>(SE[div - 2].second, N - 1);

  print<int, int, int>(div, SE);

  int sign = sgn(target);
  int t = sign * target;

  int result;
  for (int j = 0; j < div; j++) {

    auto leftEdge = abs(abs(A[SE[j].first]) - target);
    auto rightEdge = abs(abs(A[SE[j].second]) - target);
    print<char[], int>("edges", {leftEdge, rightEdge});

    if (leftEdge > rightEdge) {
      auto temp =
        std::vector<int>(A.begin() + SE[j].first, A.begin() + SE[j].second + 1);

      print<char[], int>("temp", temp);

      result = solutionQ(temp, target, 2);

      print<int, int>(SE[j].first, result);

      return (result > -1 ? result + SE[j].first : -1);
    }
  }
  return (A[0] == target ? 0 : -1);
} // solution


int solution(const std::vector<int>& A, const int& target)
{
  return solutionQ(A, target, 2);
}


int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(-N, N);

  int target;
  std::vector<int> vector = gen.randomUniqueVector(N);

  std::sort(vector.begin(), vector.end());
  std::rotate(
    vector.begin(),
    vector.begin() + [&gen]() -> int
    {
      int rot = gen();
      while (rot < 0) {
        rot = gen();
      }
      return rot;
    }(),
    vector.end());

  auto M = [&gen]() -> int
  {
    int x = gen();
    while ((0 <= x) && (x < N)) {
      x = gen();
    }
    return x;
  }();
  target = vector[M];

  //   vector = {3, 4, 5, 1, 2};
  //   target = 1; // 3

  //   vector = {4, 5, 6, 7, 0, 1, 2};
  //   target = 0; // 4

  //   vector = {4, 5, 6, 7, 0, 1, 2};
  //   target = 3; // -1

  //   vector = {0};
  //   target = 1; // -1

  //   vector = {1, 3, 5};
  //   target = 1; // 0

  vector = {3, -3, -2, -1, 0, 1, 2};
  target = -2; // 2
  target = 2;  // 6
  target = 4;  // -1
  target = 0;  // 4

  print<char[], int>("vector", vector);
  print<char[], int>("target", target);

  print<char[], int>("result", solution(vector, target));

  return 0;
} // main