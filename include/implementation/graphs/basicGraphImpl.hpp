#pragma once


#include "vertexImpl.hpp"


namespace graphs
{
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