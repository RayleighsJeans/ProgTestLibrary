#pragma once


#include "../header.hpp"


namespace graphs
{
template <typename VertexType>
class VertexAdjacency : public std::vector<VertexType>
{
 public:
  bool addAdj(VertexType toVertex)
  {
    for (auto to : *this) {
      if (to == toVertex) {
        std::cout << "Vertex '" << toVertex->key() << "' already a neighbor"
                  << std::endl;
        return false;
      }
    }
    this->push_back(toVertex);
    return true;
  }

  bool removeAdj(VertexType toVertex)
  {
    for (auto to = this->begin(); to != this->end(); to++) {
      if (*to == toVertex) {
        this->erase(to);
        return true;
      }
    }
    std::cout << "\nVertex has no neighbour '" << toVertex->key() << "'"
              << std::endl;
    return false;
  }

  bool hasAdj(VertexType toVertex) const
  {
    for (auto& to : *this) {
      if (to == toVertex) {
        return true;
      }
    }
    return false;
  }
};


template <typename KeyType>
class BasicVertex
{
 protected:
  KeyType m_key;

  using Edges = VertexAdjacency<BasicVertex<KeyType>*>;
  Edges m_edges;


 public:
  BasicVertex(KeyType s) : m_key(s) {}
  ~BasicVertex() = default;

  KeyType key() const { return m_key; }

  bool addAdj(BasicVertex<KeyType>* toVertex)
  {
    return m_edges.addAdj(toVertex);
  }

  bool removeAdj(BasicVertex<KeyType>* toVertex)
  {
    return m_edges.removeAdj(toVertex);
  }

  bool hasAdj(BasicVertex<KeyType>* toVertex)
  {
    return m_edges.hasAdj(toVertex);
  }

  Edges getNeighbors() const { return m_edges; }
};


template <typename KeyType, typename VertexType>
class VertexMap : public std::map<KeyType, VertexType*>
{
 public:
  bool addVertex(VertexType* v)
  {
    if (!v)
      return false;
    if (this->find(v->key()) == this->end()) {
      this->operator[](v->key()) = v;
      return true;
    }
    std::cout << "Vertex '" << v->key() << "' already exists" << std::endl;
    return false;
  }

  bool hasVertex(VertexType* v)
  {
    if (!v)
      return false;
    return (this->find(v->key()) != this->end());
  }
};


template <typename KeyType, typename VertexType>
class AdjacencyMatrix
    : public std::vector<std::vector<std::pair<KeyType, bool>>>
{
 private:
  VertexMap<KeyType, VertexType>* m_map;


 public:
  AdjacencyMatrix(VertexMap<KeyType, VertexType>* map) : m_map(map) {}

  void update()
  {
    this->clear();
    std::vector<std::pair<KeyType, bool>> vertexList;
    for (auto& [keyA, vertexA] : *m_map) {
      for (auto& [keyB, vertexB] : *m_map) {
        vertexList.push_back(
          std::pair<KeyType, bool>(vertexB->key(), vertexB->hasAdj(vertexA)));
      }

      this->push_back(vertexList);
      vertexList.clear();
    }
  }
};


template <typename KeyType, typename VertexType>
class DefaultGraph
{
 public:
  virtual void DFS(std::vector<bool> visited = std::vector<bool>(),
                   VertexType* startVertex = nullptr) = 0;
  virtual void BFS(VertexType* startVertex = nullptr) = 0;
};


template <typename KeyType>
class BasicGraph : public DefaultGraph<KeyType, BasicVertex<KeyType>>
{
 private:
  using VertexType = BasicVertex<KeyType>;

  VertexMap<KeyType, VertexType>* m_map;
  AdjacencyMatrix<KeyType, VertexType> m_matrix;


 public:
  BasicGraph(VertexType* fromVertex, VertexType* toVertex)
      : m_map(new VertexMap<KeyType, VertexType>()),
        m_matrix(AdjacencyMatrix<KeyType, VertexType>(m_map))
  {
    m_map->addVertex(fromVertex);
    m_map->addVertex(toVertex);
    fromVertex->addAdj(toVertex);
    m_matrix.update();
  }
  BasicGraph() = default;
  ~BasicGraph() = default;

  bool addVertex(VertexType* fromVertex, VertexType* toVertex)
  {
    if (m_map->addVertex(fromVertex) || m_map->addVertex(toVertex)) {
      fromVertex->addAdj(toVertex);
      m_matrix.update();
      return true;
    }
    return false;
  }

  bool addAdj(VertexType* fromVertex, VertexType* toVertex)
  {
    if (m_map->hasVertex(fromVertex) && m_map->hasVertex(toVertex)) {
      fromVertex->addAdj(toVertex);
      m_matrix.update();
      return true;
    }
    return false;
  }

  bool removeAdj(VertexType* fromVertex, VertexType* toVertex)
  {
    if (m_map->hasVertex(fromVertex) && m_map->hasVertex(toVertex)) {
      fromVertex->removeAdj(toVertex);
      m_matrix.update();
      return true;
    }
    return false;
  }

  void removeVertex(VertexType* target)
  {
    if (!m_map->hasVertex(target)) {
      std::cout << "Vertex '" << target->key() << "' doesn't exist"
                << std::endl;
      return;
    }

    VertexType* parent = nullptr;
    for (auto& [key, fromVertex] : *m_map) {
      if (fromVertex->hasAdj(target)) {
        if (!parent) {
          parent = fromVertex;
        }
        else {
          fromVertex->removeAdj(target);
        }
      }
    }

    parent->removeAdj(target);
    for (auto& neighbor : target->getNeighbors()) {
      parent->addAdj(neighbor);
    }

    m_map->erase(target->key());
    m_matrix.update();
  }

  void BFS(VertexType* startVertex = nullptr) override
  {
    if (!startVertex)
      startVertex = m_map->begin()->second;
    if (!m_map->hasVertex(startVertex)) {
      std::cout << "Vertex '" << startVertex->key() << "' not in graph"
                << std::endl;
      return;
    }

    std::vector<bool> visited(m_map->size(), false);
    std::list<VertexType*> queue;

    visited[std::distance(m_map->begin(), m_map->find(startVertex->key()))] =
      true;

    queue.push_back(startVertex);
    while (!queue.empty()) {
      VertexType* vertex = queue.front();
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
  }

  void DFS(std::vector<bool> visited = std::vector<bool>(),
           VertexType* startVertex = nullptr) override
  {
    if (!startVertex)
      startVertex = m_map->begin()->second;
    if (!m_map->hasVertex(startVertex)) {
      std::cout << "Vertex '" << startVertex->key() << "' not in graph "
                << std::endl;
      return;
    }

    if (visited.empty())
      visited = std::vector<bool>(m_map->size(), false);

    visited[std::distance(m_map->begin(), m_map->find(startVertex->key()))] =
      true;
    std::cout << "Visited '" << startVertex->key() << "'" << std::endl;

    for (auto& neighbour : startVertex->getNeighbors()) {
      int D = std::distance(m_map->begin(), m_map->find(neighbour->key()));
      if (!visited[D])
        DFS(visited, neighbour);
    }
  }

  void print()
  {
    std::cout << "Graph:" << std::endl;
    int i = 0;
    for (const auto& innerList : m_matrix) {
      if (i == 0) {
        std::cout << "\t";
        for (const auto& entry : innerList) {
          std::cout << entry.first << "\t";
        }
        std::cout << std::endl;
      }
      std::cout << innerList[i].first << "\t";

      for (const auto& entry : innerList) {
        std::cout << entry.second << "\t";
      }
      std::cout << std::endl;
      i++;
    }
  }
};
} // namespace graphs