#include "../include/header.hpp"
#include "fizzBuzzSampleTest.hpp"


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
  int n = 15;
  fizzBuzz(n);

  return 0;
}
