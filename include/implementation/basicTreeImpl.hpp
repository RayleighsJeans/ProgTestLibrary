#pragma once


#include "basicGraphImpl.hpp"


namespace trees
{
template <typename KeyType>
class Node : public graphs::BasicVertex<KeyType>
{
 private:
  using NodeType = Node<KeyType>;

  size_t m_kary;

  using Edges = graphs::VertexAdjacency<Node<KeyType>*>;
  Edges m_edges;


 public:
  Node(KeyType key, size_t kary)
      : graphs::BasicVertex<KeyType>(key), m_kary(kary)
  {
    for (size_t i = 0; i < m_kary; i++)
      m_edges.push_back(nullptr);
  };
  ~Node() = default;

  NodeType* addAdj(NodeType* node)
  {
    KeyType max = minValueKey();
    NodeType* root = nullptr;

    size_t i;
    for (i = 0; i < m_kary; i++) {
      if (!m_edges[i] || m_edges[i] == node) {
        m_edges[i] = node;
      }

      if (max < m_edges[i]->key()) {
        max = std::max(max, m_edges[i]->key());
        root = m_edges[i];
      }
    }
    std::cout << " " << i << " " << root << " ";
    if (root)
      std::cout << root->key();
    std::cout << std::endl;
    return (i == m_kary ? root : nullptr);
  }

  bool removeAdj(Node<KeyType>* node)
  {
    for (int i = 0; i < m_kary; i++) {
      if (m_edges[i] == node) {
        m_edges[i] = nullptr;
        return true;
      }
    }
    return false;
  }

  bool hasAdj(Node<KeyType>* node) { return m_edges.hasAdj(node); }

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
    }

    for (NodeType* root : m_edges) {
      while (!queue.empty() && root) {
        root = root->addAdj(queue.back());
        queue.pop_back();
      }
    }
    m_kary = kary;
  }

  KeyType minValueKey() const
  {
    bool flag = false;
    KeyType min;
    for (NodeType* node : m_edges) {
      if (node) {
        flag = true;
        min = std::min(min, node->key());
      }
    }
    return (flag ? min : KeyType());
  }

  Edges getNeighbors() const { return m_edges; }

  void show() const
  {
    for (NodeType* node : m_edges) {
      if (node)
        std::cout << node->key() << ", ";
      else
        std::cout << "*, ";
    }
  }
};


template <typename KeyType>
class BasicTree : public graphs::DefaultGraph<KeyType, Node<KeyType>>
{
 private:
  using NodeType = Node<KeyType>;
  NodeType* m_root;

  graphs::VertexMap<KeyType, NodeType>* m_map;
  graphs::AdjacencyMatrix<KeyType, NodeType> m_matrix;

  size_t m_kary;


 public:
  BasicTree(const size_t kary, const KeyType& key)
      : BasicTree(kary, new NodeType(key, kary)) {};
  BasicTree(size_t kary, NodeType* node)
      : m_root(node),
        m_map(new graphs::VertexMap<KeyType, NodeType>()),
        m_matrix(graphs::AdjacencyMatrix<KeyType, NodeType>(m_map)),
        m_kary(kary)
  {
    m_map->addVertex(m_root);
  }

  ~BasicTree() = default;

  NodeType* insertNodes(std::vector<NodeType*> nodes)
  {
    NodeType* root(m_root);
    NodeType* tmp = nullptr;

    size_t i = 0;
    while (root && i < nodes.size()) {
      nodes[i]->changeKary(m_kary);
      m_map->addVertex(nodes[i]);

      std::cout << "i " << i << " node " << nodes[i]->key() << " root "
                << root->key();
      tmp = root->addAdj(nodes[i]);
      std::cout << " tmp " << tmp << std::endl;

      root = (!tmp ? root : tmp);
      i++;
    }
    return root;
  }

  //   NodeType* insertNode(NodeType* root, NodeType* node)
  //   {
  //     if (!node)
  //       return (Node<V>(key));
  //     if (key < node->key) {
  //       node->left = insertNode(node->left, key);
  //     }
  //     else if (key > node->key) {
  //       node->right = insertNode(node->right, key);
  //     }
  //     else {
  //       return node;
  //     }
  //     return node;
  //   }

  //   void appendNode(NodeType* node) { while () }


  //   Node<V>* rightRotate(Node<V>* root)
  //   {
  //     Node<V>* x = root->left;
  //     Node<V>* y = x->right;
  //     x->right = root;
  //     root->left = y;
  //     return x;
  //   }

  //   Node<V>* leftRotate(Node<V>* root)
  //   {
  //     Node<V>* x = root->right;
  //     Node<V>* y = x->left;
  //     x->left = root;
  //     root->right = y;
  //     return y;
  //   }


  //   Node<V>* minimumValueNode(Node<V>* node)
  //   {
  //     Node<V>* current = node;
  //     while (current->left != nullptr)
  //       current = current->left;
  //     return current;
  //   }

  //   Node<V>* remove(Node<V>* root, int key)
  //   {
  //     if (!root)
  //       return root;

  //     if (key < root->key) {
  //       root->left = remove(root->left, key);
  //     }
  //     else if (key > root->key) {
  //       root->right = remove(root->right, key);
  //     }
  //     else {
  //       if ((!root->left) || (!root->right)) {
  //         Node<V>* temp = root->left ? root->left : root->right;
  //         if (!temp) {
  //           temp = root;
  //           root = nullptr;
  //         }
  //         else {
  //           *root = *temp;
  //         }
  //         free(temp);
  //       }
  //       else {
  //         Node<V>* temp = minimumValueNode(root->right);
  //         root->key = temp->key;
  //         root->right = remove(root->right, temp->key);
  //       }
  //     }
  //     return root;
  //   }

  //   void print(Node<V>* root, std::string indent, bool last)
  //   {
  //     if (root != nullptr) {
  //       std::cout << indent;
  //       if (last) {
  //         std::cout << "R----";
  //         indent += "   ";
  //       }
  //       else {
  //         std::cout << "L----";
  //         indent += "|  ";
  //       }
  //       std::cout << root->key << std::endl;
  //       print(root->left, indent, false);
  //       print(root->right, indent, true);
  //     }
  //   }

  void DFS(std::vector<bool> visited = std::vector<bool>(),
           NodeType* startVertex = nullptr) {};

  void BFS(NodeType* startVertex = nullptr) {};

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