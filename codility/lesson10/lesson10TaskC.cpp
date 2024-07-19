#include <cmath>

#include <fstream>
#include <iostream>

#include <algorithm>
#include <array>
#include <map>
#include <vector>

#include <limits>
#include <random>

std::string filename = "lesson10TaskC.txt";
constexpr int N = 400000;         // 400000;
constexpr int limit = 1000000000; // 1000000000;

int solution(std::vector<int>& A)
{
  std::vector<int> peaks = [&A]() -> std::vector<int>
  {
    std::vector<int> indices;
    for (int i = 1; i < A.size() - 1; i++)
      if ((A[i - 1] < A[i]) && (A[i + 1] < A[i]))
        indices.push_back(i);
    return indices;
  }();

  if (peaks.empty())
    return 0;
  if (peaks.size() == 1)
    return 1;

  std::vector<int> distances = [&peaks]() -> std::vector<int>
  {
    std::vector<int> L(peaks.size() - 1, 0);
    for (int i = 0; i < peaks.size() - 1; i++)
      L[i] = peaks[i + 1] - peaks[i];
    return L;
  }();

  if (distances.empty())
    return 0;

  auto contract = [](int K, const std::vector<int>& arr)
  {
    std::vector<int> contraction;
    int M = 0;

    int sum = 0;
    while (M < arr.size()) {
      sum += arr[M];
      M++;
      if (sum >= K) {
        contraction.push_back(sum);
        sum = 0;
      }
    }
    return contraction;
  };

  if (*std::min_element(distances.begin(), distances.end()) >= peaks.size())
    return peaks.size();

  std::vector<int> contraction = distances;

  int K = 1;
  while (K <= peaks.size()) {
    contraction = contract(K, distances);

    if (contraction.size() + 1 < K)
      return K - 1;
    K++;
  }
  return -1;
} // solution

int solutionB(std::vector<int>& A)
{

  if (A.size() < 3)
    return 0;

  std::vector<int> peaks(A.size());

  int last_peak = -1;
  peaks.back() = last_peak;

  for (auto i = ++A.rbegin(); i != --A.rend(); i++) {
    int index = A.size() - (i - A.rbegin()) - 1;
    if (*i > *(i - 1) && *i > *(i + 1))
      last_peak = index;
    peaks[index] = last_peak;
  }

  peaks.front() = last_peak;

  int max_flags = 0;

  for (int i = 1; i * i <= A.size() + i; i++) {
    int next_peak = peaks[0];
    int flags = 0;

    for (int j = 0; j < i && next_peak != -1; j++, flags++) {
      if (next_peak + i >= A.size())
        next_peak = -1;
      else
        next_peak = peaks[next_peak + i];
    }
    max_flags = std::max(max_flags, flags);
  }

  return max_flags;
}

int main()
{
  auto printVector = []<typename T>(auto& name, std::vector<T>& arr)
  {
    std::cout << ">> " << name << ": {";
    for (auto& a : arr) {
      std::cout << a << ", ";
    }
    std::cout << "}." << std::endl;
  };

  std::ofstream file;
  file.open(filename); //, std::ios_base::app);

  auto write2File = [&file]<typename T>(std::vector<T> outVector)
  {
    file << "[";
    for (size_t it = 0; it < outVector.size(); it++) {
      file << outVector.at(it);
      if (it != outVector.size() - 1)
        file << ", ";
    }
    file << "]";
  };

  std::random_device randDevice;
  std::mt19937 generator(randDevice());

  std::uniform_int_distribution<> distributionA(1, N);
  std::uniform_int_distribution<> distributionB(0, limit);

  auto gen = [&distributionB, &generator]()
  {
    return distributionB(generator);
  };

  std::vector<int> rndVector(distributionA(generator));
  std::generate(rndVector.begin(), rndVector.end(), gen);

  // printVector("rndVector", rndVector);
  auto res = solution(rndVector);
  std::cout << ">> res " << res << ", " << solutionB(rndVector) << std::endl;

  write2File(rndVector);
  file << std::endl;

  return 0;
} // main