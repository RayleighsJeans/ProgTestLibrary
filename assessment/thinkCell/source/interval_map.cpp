#include "../include/interval_map.hpp"


int main()
{

  interval_map<int, char>* map = new interval_map<int, char>('a');

  map->assignTest(3, 5, 'b');

  return 0;
}