#include "../../include/header.hpp"


using namespace helper;


template <typename K, typename V>
class LRUCache
{
 private:
  int m_capacity;
  int m_size = 0;
  std::map<K, std::pair<V, int>> m_container;
  std::vector<K> m_cache;


 private:
  void updateCache(K key)
  {
    m_cache.push_back(key);
    std::rotate(m_cache.begin(), m_cache.begin() + m_size - 1, m_cache.end());

    updateContainer();
    m_container[key].second = 0;
  }

  void updateContainer()
  {
    for (auto& [key, value] : m_container) {
      m_container[key].second++;
    }
  }


 public:
  LRUCache(int capacity) : m_capacity(capacity) {}

  int get(K key)
  {
    if (!m_size || !m_capacity || !m_container.count(key))
      return -1;

    if (m_cache.size() > 0)
      m_cache.erase(m_cache.begin() + m_container[key].second);
    updateCache(key);
    m_container[key].second = 0;

    return m_container[key].first;
  }

  void put(K key, V value)
  {
    if (m_size < m_capacity) {
      if (m_container.count(key) > 0)
        m_container[key].first = value;
      else
        m_container[key] = std::pair<K, V>(value, 0);
      m_size++;
    }
    else {
      if (m_container.count(key) > 0) {
        m_container[key].first = value;
        if (m_cache.size() > 0)
          m_cache.erase(m_cache.begin() + m_container[key].second);
      }
      else {
        m_container.erase(m_cache.back());
        m_container[key] = std::pair<K, V>(value, 0);
        m_cache.pop_back();
      }
    }
    updateCache(key);
  }

  void debug()
  {
    std::cout << "[container] - ";
    for (auto& [key, value] : m_container) {
      std::cout << "<" << key << ":";
      print<V, int>(value);
      std::cout << "> ";
    }
    std::cout << std::endl;

    print<char[], int>("LRU cache", m_cache);
  }
}; // LRUCache

using cache = LRUCache<int, int>;


int main()
{
  //   cache* lRUCache = new cache(2);
  //   lRUCache->put(1, 1);                                // cache is {1=1}
  //   lRUCache->put(2, 2);                                // cache is {1=1,
  //   2=2} print<char[], int>("get(1) (1)", lRUCache->get(1)); // return 1
  //   lRUCache->put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
  //   lRUCache->debug();
  //   print<char[], int>("get(2) (-1)", lRUCache->get(2)); // return -1
  //   lRUCache->put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
  //   lRUCache->debug();
  //   print<char[], int>("get(1) (-1)", lRUCache->get(1)); // return -1
  //   print<char[], int>("get(3) (3)", lRUCache->get(3));  // return 3
  //   print<char[], int>("get(4) (4)", lRUCache->get(4));  // return 4


  //   ["LRUCache","put","put","put","put","get","get","get","get","put","get","get","get","get","get"]
  //   [[3],[1,1],[2,2],[3,3],[4,4],[4],[3],[2],[1],[5,5],[1],[2],[3],[4],[5]]
  // [null,null,null,null,null,4,3,2,-1,null,-1,2,3,-1,5]
  cache* lRUCache = new cache(3);
  lRUCache->put(1, 1);
  lRUCache->put(2, 2);
  lRUCache->put(3, 3);
  lRUCache->put(4, 4);
  lRUCache->debug();

  print<char[], int>("get(4) (4)", lRUCache->get(4));
  print<char[], int>("get(3) (3)", lRUCache->get(3));
  print<char[], int>("get(2) (2)", lRUCache->get(2));
  print<char[], int>("get(1) (-1)", lRUCache->get(1));
  lRUCache->debug();

  // lRUCache->put(5, 5);
  // lRUCache->debug();

  // print<char[], int>("get(1) (-1)", lRUCache->get(-1));
  // print<char[], int>("get(2) (2)", lRUCache->get(2));
  // print<char[], int>("get(3) (3)", lRUCache->get(3));
  // print<char[], int>("get(4) (-1)", lRUCache->get(-1));
  // print<char[], int>("get(5) (5)", lRUCache->get(5));
  // lRUCache->debug();

  return 0;
} // main