
#pragma once


#include "../lists/linkedListImpl.hpp"


namespace graphs
{
template <typename VertexType, typename KeyType>
class AdjacencyList : public linked_lists::LinkedList<KeyType>
{
 private:
  using List = linked_lists::LinkedList<KeyType>;
  using K = KeyType;

 protected:
  using List::back;
  using List::front;
  using List::insert;
  using List::pop_back;
  using List::pop_front;
  using List::push_back;
  using List::push_front;

 public:
  AdjacencyList(VertexType* vertex) : List::LinkedList(vertex){};

  AdjacencyList(const K& key) : List::LinkedList(key){};

  AdjacencyList() : List::LinkedList(){};

  bool put(VertexType* toVertex)
  {
    if (List::find(toVertex, false) != List::size()) {
      std::cout << "Vertex: " << *toVertex << " already adjacent." << std::endl;
      return false;
    }
    List::push_back(toVertex);
    return true;
  }

  void put(const K& key) { List::push_back(key); }
};


// template <typename VertexType, typename KeyType, typename EdgeType>
// class AdjacencyEdgeList : public linked_lists::LinkedEdgeList<KeyType,
// EdgeType>
// {
//  private:
//   using K = KeyType;
//   using E = EdgeType;

//   using List = linked_lists::LinkedEdgeList<K, E>;

//  protected:
//   using List::back;
//   using List::front;
//   using List::insert;
//   using List::pop_back;
//   using List::pop_front;
//   using List::push_back;
//   using List::push_front;

//  public:
//   AdjacencyEdgeList(VertexType* vertex) : List::LinkedEdgeList(vertex){};

//   AdjacencyEdgeList(const K key) : List::LinkedEdgeList(key){};

//   AdjacencyEdgeList() : List::LinkedEdgeList(){};

//   bool put(const E& edge, VertexType* toVertex)
//   {
//     if (List::find(toVertex, false) != List::size()) {
//       std::cout << "Vertex: " << *toVertex << " already adjacent." <<
//       std::endl; return false;
//     }
//     List::push_back(edge, toVertex);
//     return true;
//   }

//   void put(const E& edge, const K& key) { List::push_back(edge, key); }

//   std::optional<E>& cost(VertexType* vertex) const
//   {
//     return List::edgeTo(vertex);
//   }

//   std::optional<E> cost(const K& vertex) const { return List::edgeTo(vertex);
//   }
// };


// template <typename KeyType, typename VertexType>
// class VertexMap : public std::map<KeyType, VertexType*>
// {
//  public:
//   bool operator[](VertexType* vertex)
//   {
//     if (!vertex)
//       return false;

//     if (this->find(vertex->key()) == this->end()) {
//       std::map<KeyType, VertexType*>::operator[](vertex->key()) = v;
//       return true;
//     }
//     std::cout << "Vertex '" << vertex->key() << "' already exists" <<
//     std::endl; return false;
//   }

//   bool hasVertex(VertexType* v)
//   {
//     if (!v)
//       return false;
//     return (this->find(v->key()) != this->end());
//   }
// };


// template <typename KeyType, typename VertexType>
// class AdjacencyMatrix
//     : public std::vector<std::vector<std::pair<KeyType, bool>>>
// {
//  private:
//   VertexMap<KeyType, VertexType>* m_map;

//  public:
//   AdjacencyMatrix(VertexMap<KeyType, VertexType>* map) : m_map(map) {}

//   void update()
//   {
//     this->clear();
//     std::vector<std::pair<KeyType, bool>> vertexList;
//     for (auto& [keyA, vertexA] : *m_map) {
//       for (auto& [keyB, vertexB] : *m_map) {
//         vertexList.push_back(
//           std::pair<KeyType, bool>(vertexB->key(),
//           vertexB->hasAdj(vertexA)));
//       }

//       this->push_back(vertexList);
//       vertexList.clear();
//     }
//   }
// };
} // namespace graphs