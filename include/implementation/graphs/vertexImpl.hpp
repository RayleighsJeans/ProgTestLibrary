#pragma once


#include "../lists/nodesImpl.hpp"
#include "adjacencyImpl.hpp"


namespace graphs
{
template <typename KeyType>
class BasicVertex : public linked_lists::Node<KeyType>
{
 public:
  BasicVertex(KeyType key) : linked_lists::Node<KeyType>::Node(key){};

  BasicVertex() : linked_lists::Node<KeyType>::Node(){};

  ~BasicVertex() = default;

  KeyType key() const { return linked_lists::Node<KeyType>::label(); }

  KeyType operator()() const
  {
    return linked_lists::Node<KeyType>::operator()();
  }

  void operator()(KeyType key) { linked_lists::Node<KeyType>::operator()(key); }

  friend std::ostream& operator<<(std::ostream& stream,
                                  BasicVertex<KeyType>& vertex)
  {
    return (stream << "{" << vertex() << "}");
  }
};


template <typename KeyType>
class Vertex : public BasicVertex<KeyType>
{
 private:
  AdjacencyList<Vertex<KeyType>, KeyType> m_edges;

 public:
  Vertex(const KeyType key) : BasicVertex<KeyType>::BasicVertex(key){};

  Vertex() : BasicVertex<KeyType>::BasicVertex(){};

  ~Vertex() = default;

  bool connect(Vertex<KeyType>* toVertex) { return m_edges.put(toVertex); }

  void connect(const KeyType key) { m_edges.put(key); }

  void remove(Vertex<KeyType>* toVertex) { m_edges.erase(toVertex); }

  void remove(const KeyType key) { m_edges.erase(key); }

  std::optional<size_t> find(Vertex<KeyType>* toVertex)
  {
    const size_t at = m_edges.find(toVertex);
    return (at != m_edges.size() ? std::optional<size_t>(at) : std::nullopt);
  };

  const AdjacencyList<Vertex<KeyType>, KeyType>& edges() const
  {
    return m_edges;
  }

  friend std::ostream& operator<<(std::ostream& stream,
                                  const Vertex<KeyType>& vertex)
  {
    stream << "{" << vertex.key() << " -> " << vertex.edges() << "}";
    return stream;
  }
};


template <typename KeyType, typename EdgeType>
class EdgeVertex : public linked_lists::EdgeNode<KeyType, EdgeType>
{
 private:
  using Node = linked_lists::EdgeNode<KeyType, EdgeType>;

  using K = KeyType;
  using E = EdgeType;

  // AdjacencyEdgeList<Vertex<KeyType>, KeyType, EdgeType> m_edges;

 public:
  EdgeVertex(const K& key, Node* next, const E& edge)
      : Node::EdgeNode(key, next, edge){};

  EdgeVertex(const K& key, Node* next) : Node::EdgeNode(key, next, E()){};

  EdgeVertex(const K& key) : Node::EdgeNode(key, nullptr, E()){};

  EdgeVertex(Node* node) : Node::EdgeNode(node){};

  EdgeVertex() : Node::EdgeNode(){};

  ~EdgeVertex() = default;
};
} // namespace graphs