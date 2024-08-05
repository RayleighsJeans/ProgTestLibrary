#pragma once


#include "basicGraphImpl.hpp"


namespace trees
{
template <typename KeyType>
class Node : public graphs::BasicVertex<KeyType>
{
 private:
  using NodeType = Node<KeyType>;


 protected:
  size_t m_kary;
  size_t m_height = 0;
  size_t m_depth = 0;
  int m_balanceFactor = 0;
  size_t m_neighbors = 0;

  using Edges = graphs::VertexAdjacency<Node<KeyType>*>;
  Edges m_edges;


 public:
  Node(KeyType key, size_t kary)
      : graphs::BasicVertex<KeyType>(key), m_kary(kary)
  {
    for (size_t i = 0; i < m_kary; i++)
      m_edges.push_back(nullptr);
    updateHeight();
  };
  ~Node() = default;

  bool addAdj(NodeType* node)
  {
    if (node == this)
      return false;

    size_t i;
    for (i = 0; i < m_kary; i++) {
      if (!m_edges[i] || m_edges[i] == node) {
        m_edges[i] = node;
        m_neighbors++;
        updateHeight();
        return true;
      }
    }
    return false;
  }

  bool removeAdj(Node<KeyType>* node)
  {
    for (size_t i = 0; i < m_kary; i++) {
      if (m_edges[i] == node) {
        m_edges[i] = nullptr;
        m_neighbors--;

        std::list<NodeType*> parents;
        parents.push_back(this);

        for (NodeType* edge : node->getNeighbors()) {
          if (edge) {
            parents.push_back(edge);
            while (!parents.front()->addAdj(edge)) {
              parents.pop_front();
            }
          }
        }

        updateHeight();
        return true;
      }
    }
    return false;
  }

  bool hasAdj(Node<KeyType>* node) const { return m_edges.hasAdj(node); }

  void changeKary(size_t kary)
  {
    if (kary > m_kary) {
      m_kary = kary;
      return;
    }

    std::list<NodeType*> queue;
    for (size_t i = kary; i < m_kary; i++) {
      queue.push_back(m_edges.back());
      m_edges.pop_back();
      m_neighbors--;
    }

    for (NodeType* root : m_edges) {
      while (!queue.empty()) {
        while (!root->addAdj(queue.back())) {
          root = root->maxValueNode();
        }
        queue.pop_back();
      }
    }
    m_kary = kary;
  }

  void updateHeight()
  {
    size_t localBalance = std::numeric_limits<size_t>::max();
    size_t localHeight = 0;
    for (NodeType* edge : m_edges) {
      localHeight = std::max(localHeight, (edge ? edge->getHeight() : 0));
      localBalance = std::min(localBalance, (edge ? edge->getHeight() : 0));
    }
    m_height = 1 + localHeight;
    m_balanceFactor = localHeight - localBalance;
  }

  void setDepth(size_t depth) { m_depth = depth; };

  void setHeight(size_t height) { m_height = height; }

  void setBalance(int balance) { m_balanceFactor = balance; }

  NodeType* maxValueNode() const
  {
    NodeType* node = nullptr;
    KeyType max = KeyType();
    for (NodeType* edge : m_edges) {
      if (edge && edge->key() > max) {
        max = edge->key();
        node = edge;
      }
    }
    return node;
  }

  NodeType* minValueNode() const
  {
    NodeType* node = nullptr;
    KeyType min = KeyType();
    for (NodeType* edge : m_edges) {
      if (edge && min > edge->key()) {
        min = edge->key();
        node = edge;
      }
    }
    return node;
  }

  size_t neighborsSize() const { return m_neighbors; }

  Edges getNeighbors() const { return m_edges; }

  int getBalance() const { return m_balanceFactor; }

  size_t getHeight() const { return m_height; }

  size_t getDepth() const { return m_depth; }

  void show() const
  {
    for (NodeType* node : m_edges) {
      if (node)
        std::cout << "'" << node->key() << "', ";
      else
        std::cout << "*, ";
    }
    std::cout << "\tN=" << m_neighbors << ", H=" << m_height
              << ", B=" << m_balanceFactor << ", D=" << m_depth;
  }
};


template <typename KeyType>
class BasicTree : public graphs::DefaultGraph<KeyType, Node<KeyType>>
{
 private:
  using NodeType = Node<KeyType>;


 protected:
  NodeType* m_root;

  graphs::VertexMap<KeyType, NodeType>* m_map;
  graphs::AdjacencyMatrix<KeyType, NodeType> m_matrix;

  size_t m_kary;
  size_t m_maxDepth = 0;


 public:
  BasicTree(const size_t kary, const KeyType& key)
      : BasicTree(kary, new NodeType(key, kary)){};
  BasicTree(size_t kary, NodeType* node)
      : m_root(node),
        m_map(new graphs::VertexMap<KeyType, NodeType>()),
        m_matrix(graphs::AdjacencyMatrix<KeyType, NodeType>(m_map)),
        m_kary(kary)
  {
    m_map->addVertex(m_root);
  };
  ~BasicTree() = default;

  NodeType* insertNode(NodeType* root, NodeType* node)
  {
    if (!root)
      return nullptr;

    node->changeKary(m_kary);
    m_map->addVertex(node);

    while (!root->addAdj(node)) {
      root = root->maxValueNode();
    }
    updateHeights();
    return root;
  }

  NodeType* insertNode(NodeType* node)
  {
    NodeType* root(m_root);
    return insertNode(root, node);
  }

  NodeType* insertNodes(NodeType* root, std::vector<NodeType*> nodes)
  {
    size_t i = 0;
    while (root && i < nodes.size()) {
      root = insertNode(root, nodes[i]);
      i++;
    }
    return root;
  }

  NodeType* insertNodes(std::vector<NodeType*> nodes)
  {
    NodeType* root(m_root);
    return insertNodes(root, nodes);
  }

  NodeType* removeNode(NodeType* node)
  {
    if (!m_map->hasVertex(node))
      std::cout << "Node '" << node->key() << "' not in tree" << std::endl;

    for (auto& [key, parent] : m_map) {
      if (parent->hasVertex(node)) {
        parent->removeAdj(node);
        updateHeights();
        return parent;
      }
    }
    return nullptr;
  }

  void updateHeights()
  {
    size_t totalDepth = 0;
    std::function<void(NodeType*, size_t)> updateChildsHeight =
      [&](NodeType* root, size_t currentDepth) -> void
    {
      for (NodeType* edge : root->getNeighbors()) {
        if (edge)
          updateChildsHeight(edge, currentDepth + 1);
      }
      root->updateHeight();
      root->setDepth(currentDepth);
      totalDepth = std::max(totalDepth, currentDepth);
    };
    updateChildsHeight(m_root, 1);
    m_maxDepth = totalDepth;
  }

  void balanceTree(NodeType* root = nullptr)
  {
    if (!root)
      root = m_root;

    std::list<NodeType*> parentQueue;
    std::list<std::pair<NodeType*, NodeType*>> childQueue;

    if (root->neighborsSize() < m_kary)
      parentQueue.push_back(root);

    std::function<void(NodeType*)> unbalancedNodes =
      [&](NodeType* parent) -> void
    {
      size_t B = parent->getBalance();
      for (NodeType* node : parent->getNeighbors()) {
        if (!node)
          continue;

        size_t N = node->neighborsSize();
        if ((N < m_kary) && (node->getDepth() < m_maxDepth - 1))
          parentQueue.push_back(node);
        if (N == 0 && B <= 1)
          childQueue.push_back(std::pair<NodeType*, NodeType*>(parent, node));

        unbalancedNodes(node);
      }
    };

    auto balanceLoop = [&parentQueue, &childQueue]() -> int
    {
      int actionCounter = 0;
      NodeType* parent = parentQueue.front();

      while (!childQueue.empty() && !parentQueue.empty()) {

        while ((childQueue.back().second->neighborsSize() == 0) &&
               parent->addAdj(childQueue.back().second)) {
          childQueue.back().first->removeAdj(childQueue.back().second);
          childQueue.pop_back();
          actionCounter++;
        }

        if (childQueue.back().second == parent ||
            childQueue.back().second->neighborsSize() > 0) {
          if (!childQueue.empty())
            childQueue.pop_back();
        }
        else {
          parentQueue.pop_front();
          parent = parentQueue.front();
        }
      }
      return actionCounter;
    };

    unbalancedNodes(root);
    while (balanceLoop() > 0) {
      updateHeights();
      childQueue.clear();
      parentQueue.clear();
      unbalancedNodes(root);
    }
  }

  NodeType* getNode(const KeyType& key) const
  {
    if (m_map->find(key) != m_map->end())
      return m_map->operator[](key);
  }

  NodeType* minValueNode(NodeType* root = nullptr)
  {
    if (!root)
      root = m_root;

    NodeType* current = root;
    while (current->minValueNode()) {
      current = current->minValueNode();
    }
    return current;
  }

  void DFS(std::vector<bool> visited = std::vector<bool>(),
           NodeType* root = nullptr)
  {
    if (!root)
      root = m_root;
    if (!m_map->hasVertex(root)) {
      std::cout << "Vertex '" << root->key() << "' not in graph " << std::endl;
      return;
    }

    if (visited.empty())
      visited = std::vector<bool>(m_map->size(), false);

    visited[std::distance(m_map->begin(), m_map->find(root->key()))] = true;
    std::cout << "Visited '" << root->key() << "'" << std::endl;

    for (auto& neighbour : root->getNeighbors()) {
      int D = std::distance(m_map->begin(), m_map->find(neighbour->key()));
      if (!visited[D])
        DFS(visited, neighbour);
    }
  }

  void BFS(NodeType* root = nullptr)
  {
    if (!root)
      root = m_map->begin()->second;
    if (!m_map->hasVertex(root)) {
      std::cout << "Vertex '" << root->key() << "' not in graph" << std::endl;
      return;
    }

    std::vector<bool> visited(m_map->size(), false);
    std::list<NodeType*> queue;

    visited[std::distance(m_map->begin(), m_map->find(root->key()))] = true;

    queue.push_back(root);
    while (!queue.empty()) {
      NodeType* vertex = queue.front();
      std::cout << "Visited '" << vertex->key() << "'" << std::endl;
      queue.pop_front();

      for (auto& neighbour : vertex->getNeighbors()) {
        int D = std::distance(m_map->begin(), m_map->find(neighbour->key()));
        if (!visited[D]) {
          visited[D] = true;
          queue.push_back(neighbour);
        }
      }
    }
  };

  void show()
  {
    std::cout << "root: " << m_root->key() << std::endl;
    for (auto& [key, node] : *m_map) {
      std::cout << "'" << key << "' -> ";
      node->show();
      std::cout << std::endl;
    }
  }
}; // class BasicTree
} // namespace trees