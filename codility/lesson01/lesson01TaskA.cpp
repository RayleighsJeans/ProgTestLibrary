#include "../../include/header.hpp"

#include <bitset>


constexpr int limit = 10; // std::numeric_limits<int>::max();


using namespace helper;


int solution(int N)
{
  int maxGap = 0;
  int binGapCount = 0;

  bool startCount = false;

  for (; N > 0; N >>= 1) {
    if (N & 1)
      startCount = true;

    if (startCount) {
      if (!(N & 1)) {
        binGapCount++;
      }
      else {
        maxGap = std::max(maxGap, binGapCount);
        binGapCount = 0;
      }
    }
  }
  return maxGap;
} // solution


int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(1, limit);

  int number = 0;
  int res = -1;
  std::bitset<32UL> bin;
  for (int i = 0; i < 10; i++) {
    number = gen();
    bin = std::bitset<32>(number);
    res = solution(number);

    std::cout << ">> n:" << number << "; binary:" << bin << "; N:" << res
              << std::endl;

    file(number);
    file(bin.to_string().c_str());
    file(res);
    file.flush();
  }

  return 0;
} // main
