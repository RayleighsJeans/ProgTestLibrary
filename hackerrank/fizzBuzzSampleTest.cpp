#include "../include/header.hpp"
#include "fizzBuzzSampleTest.hpp"


constexpr int N = 10;     // 100000
constexpr int limit = 10; // std::numeric_limits<int>::max


using namespace helper;


void fizzBuzz(int n)
{
  for (int i = 1; i <= n; i++) {
    if ((i % 5 == 0) && (i % 3 == 0)) {
      std::cout << "FizzBuzz" << std::endl;
    }
    else if (i % 3 == 0) {
      std::cout << "Fizz" << std::endl;
    }
    else if (i % 5 == 0) {
      std::cout << "Buzz" << std::endl;
    }
    else {
      std::cout << i << std::endl;
    }
  }
}


int main()
{
  // std::string n_temp;
  // getline(std::cin, n_temp);
  // int n = stoi(ltrim(rtrim(n_temp)));

  int n = 15;
  fizzBuzz(n);

  return 0;
}
