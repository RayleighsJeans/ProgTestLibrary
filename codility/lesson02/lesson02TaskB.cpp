#include "../../include/header.hpp"


constexpr int N = 10;
constexpr int limit = 10;


int solution(std::vector<int>& A)
{
  std::unordered_map<int, int> map{};
  for (auto& a : A) {
    auto it(map.find(a));
    if (it != map.end()) {
      map.erase(it);
    }
    else {
      map[a] = 1;
    }
  }
  return map.begin()->first;
}

template <typename T>
std::vector<T> randomPairVector()
{
  helper::RandomGenerator<int> gen(1, N);
  helper::RandomGenerator<int> genB(1, limit);

  int L = 0;
  while (L % 2 == 0)
    L = gen();

  std::vector<int> track(limit, 0);
  std::vector<int> vector(L, 0);

  int m = genB();
  std::vector<int> residuals;

  auto resLambda = [&residuals](std::vector<int> vec)
  {
    auto it = vec.begin();
    while ((it = std::find_if(it, vec.end(), [](int x) { return x == 0; })) !=
           vec.end()) {
      residuals.push_back(std::distance(vec.begin(), it));
      it++;
    }
  };

  for (int i = 0; i < L; i++) {
    while (track[m] >= 1) {
      m = genB();
    }

    auto emplaceRandomCount = [&residuals, &vector, &resLambda](const int n)
    {
      residuals.clear();
      resLambda(vector);
      if (residuals.empty())
        return false;

      helper::RandomGenerator<int> genC(0, residuals.size() - 1);
      auto index = residuals[genC()];
      vector[index] = n;
      return true;
    };

    for (int j = 0; j < 2; j++)
      if (!emplaceRandomCount(m))
        break;

    track[m] += 1;
  }

  return vector;
} // randomPairVector


int main()
{
  helper::WriteToFile<int> file(__FILE__);

  std::vector<int> vector;
  int result = -1;
  for (int i = 0; i < 10; i++) {

    vector = randomPairVector<int>();
    helper::print("random vector", vector);

    result = solution(vector);
    std::cout << ">> winner is " << result << std::endl;

    file(vector);
    file(result);
    file.flush();
  }

  return 0;
} // main
