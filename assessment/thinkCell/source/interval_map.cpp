#include "../include/interval_map.hpp"


int main()
{
  {
    using namespace think_cell;
    using K = KeyType<int>;
    using V = ValueType<char>;

    K key(1);
    K key2 = 2;
    K key3(5);
    V value('a');
    V value2 = 'b';

    interval_map<int, char>* map = new interval_map<int, char>(value);

    map->assignTest(K(12), K(14), V('e'));

    map->assign(key2, key3, value2);
    map->assign(K(5), K(10), V('c'));

    map->validate();

    map->assignTest(K(6), K(8), V('d'));

    map->print();
  }
  return 0;
}