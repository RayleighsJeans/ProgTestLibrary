#include "../../include/header.hpp"


using namespace helper;


class NodeCache
{
 public:
  class Node
  {
   public:
    int key;
    int val;
    Node* prev;
    Node* next;

    Node(int key, int val)
    {
      this->key = key;
      this->val = val;
    }
  };

  Node* head = new Node(-1, -1);
  Node* tail = new Node(-1, -1);

  int cap;
  std::unordered_map<int, Node*> m;

  NodeCache(int capacity)
  {
    cap = capacity;
    head->next = tail;
    tail->prev = head;
  }

  void addNode(Node* newnode)
  {
    Node* temp = head->next;

    newnode->next = temp;
    newnode->prev = head;

    head->next = newnode;
    temp->prev = newnode;
  }

  void deleteNode(Node* delnode)
  {
    Node* prevv = delnode->prev;
    Node* nextt = delnode->next;

    prevv->next = nextt;
    nextt->prev = prevv;
  }

  int get(int key)
  {
    if (m.find(key) != m.end()) {
      Node* resNode = m[key];
      int ans = resNode->val;

      m.erase(key);
      deleteNode(resNode);
      addNode(resNode);

      m[key] = head->next;
      return ans;
    }
    return -1;
  }

  void put(int key, int value)
  {
    if (m.find(key) != m.end()) {
      Node* curr = m[key];
      m.erase(key);
      deleteNode(curr);
    }

    if ((int)m.size() == cap) {
      m.erase(tail->prev->key);
      deleteNode(tail->prev);
    }

    addNode(new Node(key, value));
    m[key] = head->next;
  }
}; // NodeCache


template <typename K, typename V>
class LRUCache
{
 private:
  size_t m_size = 0;
  size_t m_capacity;
  std::map<K, std::pair<V, int>> m_container;
  std::vector<K> m_cache;


 private:
  void updateCache(K key)
  {
    m_size = m_cache.size();

    if (m_size > 0) {
      if (m_container[key].second < 0) {
        if (m_size == m_capacity)
          m_cache.pop_back();
      }
      else {
        m_cache.erase(m_cache.begin() + m_container[key].second);
      }
    }
    m_cache.insert(m_cache.begin(), key);

    updateContainer();
  }

  void updateContainer()
  {
    for (size_t i = 0; i < m_size; i++) {
      m_container[m_cache[i]].second = i;
    }
  } // updateContainer


 public:
  LRUCache(int capacity) : m_capacity(capacity)
  {
    m_container[-1] = std::pair<int, int>(-1, -1);
  }

  int get(K key)
  {
    if (!m_size || !m_capacity || !m_container.count(key))
      return -1;

    updateCache(key);
    return m_container[key].first;
  } // get

  void put(K key, V value)
  {
    if (m_size < m_capacity) {
      if (m_container.count(key) > 0) {
        m_container[key].first = value;
      }
      else {
        m_container[key] = std::pair<K, V>(value, -1);
      }
    }
    else {
      if (m_container.count(key) > 0) {
        m_container[key].first = value;
      }
      else {
        m_container.erase(m_cache.back());
        m_container[key] = std::pair<K, V>(value, -1);
      }
    }
    updateCache(key);
  } // put

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


void caseOne()
{
  cache* lRUCache = new cache(2);
  lRUCache->put(1, 1);
  lRUCache->put(2, 2);
  print<char[], int>("get(1) (1)", lRUCache->get(1));
  print<char[], int>("should be", {1, 2});
  lRUCache->put(3, 3);
  print<char[], int>("get(2) (-1)", lRUCache->get(2));
  print<char[], int>("should be", {3, 1});
  lRUCache->put(4, 4);
  print<char[], int>("get(1) (-1)", lRUCache->get(1)); // return -1
  print<char[], int>("get(3) (3)", lRUCache->get(3));  // return 3
  print<char[], int>("get(4) (4)", lRUCache->get(4));  // return 4

  lRUCache->debug();
  print<char[], int>("should be", {4, 3});
} // caseOne


void caseTwo()
{
  cache* lRUCache = new cache(3);
  lRUCache->put(1, 1);
  lRUCache->put(2, 2);
  lRUCache->put(3, 3);
  lRUCache->put(4, 4);
  print<char[], int>("get(4) (4)", lRUCache->get(4));
  print<char[], int>("get(3) (3)", lRUCache->get(3));
  print<char[], int>("get(2) (2)", lRUCache->get(2));
  print<char[], int>("get(1) (-1)", lRUCache->get(1));
  lRUCache->put(5, 5);
  print<char[], int>("get(1) (-1)", lRUCache->get(-1));
  print<char[], int>("get(2) (2)", lRUCache->get(2));
  print<char[], int>("get(3) (3)", lRUCache->get(3));
  print<char[], int>("get(4) (-1)", lRUCache->get(-1));
  print<char[], int>("get(5) (5)", lRUCache->get(5));

  lRUCache->debug();
  print<char[], int>("should be", {5, 3, 2});
} // caseTwo


void caseThree()
{
  cache* lRUCache = new cache(10);
  lRUCache->put(10, 13);
  lRUCache->put(3, 17);
  lRUCache->put(6, 11);
  lRUCache->put(10, 5);
  lRUCache->put(9, 10);
  print<char[], int>("get(13) (-1)", lRUCache->get(13));
  lRUCache->put(2, 19);
  print<char[], int>("get(2) (19)", lRUCache->get(2));
  print<char[], int>("get(3) (17)", lRUCache->get(3));
  lRUCache->put(5, 25);
  print<char[], int>("get(8) (-1)", lRUCache->get(8));
  lRUCache->put(9, 22);
  lRUCache->put(5, 5);
  lRUCache->put(1, 30);
  print<char[], int>("get(11) (-1)", lRUCache->get(11));
  lRUCache->put(9, 12);
  print<char[], int>("get(7) (-1)", lRUCache->get(7));
  print<char[], int>("get(5) (5)", lRUCache->get(5));
  print<char[], int>("get(8) (-1)", lRUCache->get(8));
  print<char[], int>("get(9) (12)", lRUCache->get(9));
  lRUCache->put(4, 30);
  lRUCache->put(9, 3);
  print<char[], int>("get(9) (3)", lRUCache->get(9));
  print<char[], int>("get(10) (5)", lRUCache->get(10));
  print<char[], int>("get(10) (5)", lRUCache->get(10));

  lRUCache->debug();
  print<char[], int>("should be", {10, 9, 4, 5, 1, 3, 2, 6});
} // caseThree


void caseFour()
{
  RandomGenerator<int> gen(-3999, 3999);
  auto pairs = gen.random2dVector(2, 2054);

  cache* lRUCache = new cache(1101);
  NodeCache* nodeCache = new NodeCache(1101);

  Timer t;
  t.tick();
  for (size_t i = 0; i < pairs.size(); i++) {
    lRUCache->put(pairs[i][0], pairs[i][1]);
  }
  for (size_t i = 0; i < pairs.size(); i++) {
    lRUCache->get(pairs[i][0]);
    lRUCache->get(pairs[i][1]);
  }
  t.tock();

  t.tick();
  for (size_t i = 0; i < pairs.size(); i++) {
    nodeCache->put(pairs[i][0], pairs[i][1]);
  }
  for (size_t i = 0; i < pairs.size(); i++) {
    nodeCache->get(pairs[i][0]);
    nodeCache->get(pairs[i][1]);
  }
  t.tock();
}

int main()
{
  // caseOne();
  // caseTwo();
  // caseThree();
  caseFour();
  return 0;
} // main