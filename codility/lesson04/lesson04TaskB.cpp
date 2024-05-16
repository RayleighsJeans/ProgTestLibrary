#include "../../include/header.hpp"


constexpr int N = 10;     // 100000;
constexpr int limit = 10; //  1000000000;


using namespace helper;


int solution(std::vector<int>& A)
{
  std::vector<bool> map(*std::max_element(A.begin(), A.end()), false);

  auto allTrue = [&map]()
  {
    return std::all_of(map.begin(), map.end(), [](bool v) { return v; });
  };

  for (size_t i = 0; i < A.size(); i++) {
    if (map[A[i] - 1])
      continue;
    map[A[i] - 1] = true;
  }

  if (allTrue())
    return 1;
  return 0;
} // solution


int main()
{
  WriteToFile<int> file(__FILE__);

  RandomGenerator<int> gen(1, N);
  RandomGenerator<int> genB(1, limit);

  RandomGenerator<int> genTF(0, 1);

  std::vector<int> vector;
  int result = -1;

  Timer t;
  t.tick();
  for (int j = 0; j < 10; j++) {

    if (genTF()) {
      for (int i = 0; i < gen(); i++)
        vector.push_back(i + 1);
      std::shuffle(vector.begin(), vector.end(), std::default_random_engine());

      if (genTF()) {
        RandomGenerator<int> genC(0, vector.size() - 1);
        vector.erase(vector.begin() + genC());
      }
    }
    else {
      vector = genB.randomVector(gen());
    }

    file(vector);
    result = solution(vector);
    file(result);
    file.flush();
  }
  t.tock();

  return 0;
}
