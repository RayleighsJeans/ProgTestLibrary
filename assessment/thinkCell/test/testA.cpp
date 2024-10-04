#include <string>
#include <vector>

#include <limits>
#include <random>

#include <assert.h>
#include <cassert>

#include <math.h>

#include "include/interval_map.hpp"


#define STYLE 2


template <typename K, typename V>
void testIntChar(const V defaultValue)
{
  auto message = [](K m, K x, K y, K z, V g, V h)
  {
    std::cout << m << " [" << x << ", " << y << "] " << z << " " << g << " ("
              << h << ")"
              << "\n";
  };

  interval_map<K, V> mIntChar(defaultValue);

  std::random_device randDevice;
  std::mt19937 generator(randDevice());

  int max = 25;
  std::uniform_int_distribution<> distribution(-max, max);

  int i, j, k;
  char c, b;
  for (int n = 0; n < 1000000; ++n) {
    i = distribution(generator);
    j = distribution(generator);
    k = (i + j) / 2;
    c = 'a' + k % 26;

    b = mIntChar[j];

    message(n, i, j, fabs(j - i), c, mIntChar[i]);

    IntervalMapTest2(mIntChar, i, j, c);
    mIntChar.assign(i, j, c);

    if (i < j) {
      for (int l = i; l < j; l++) {
        if (mIntChar[l] != c) {
          std::cout << "first test\n";
          message(n, i, j, l, c, mIntChar[l]);
          mIntChar.printMap();
          return;
        }
      }

      if ((b != c) && (mIntChar[j] == c)) {
        std::cout << "second test " << b << ' ' << c << "\n";
        message(n, i, j, j, c, mIntChar[j]);
        mIntChar.printMap();
        return;
      }
    }

    if ((mIntChar[-max - 1] != '~') || (mIntChar[max + 1] != '~')) {
      if ((mIntChar[-max - 1] != '~')) {
        std::cout << "third test " << -max << "\n";
        message(n, i, j, -max - 1, '~', mIntChar[-max - 1]);
      }
      else {
        std::cout << "third test " << max + 1 << "\n";
        message(n, i, j, max + 1, '~', mIntChar[max + 1]);
      }
      mIntChar.printMap();
      return;
    }
  }
  mIntChar.printMap();
}


int main(int argc, char* argv[]) {}