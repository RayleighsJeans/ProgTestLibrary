#pragma once


#include "basicGraphImpl.hpp"


namespace graphs
{
template <typename CostType, typename VertexType>
class VertexEdges : public std::vector<std::pair<CostType, VertexType>>
{
 public:
  void addEdge(VertexType toVertex, const CostType& cost)
  {
    for (auto to = this->begin(); to != this->end(); to++) {
      if (to->second == toVertex) {
        *to = std::pair<CostType, VertexType>(cost, toVertex);
        return;
      }
    }
    this->push_back(std::pair<CostType, VertexType>(cost, toVertex));
  }

  bool removeEdge(VertexType toVertex)
  {
    for (auto to = this->begin(); to != this->end(); to++) {
      if (to->second == toVertex) {
        this->erase(to);
        return true;
      }
    }
    std::cout << "\nVertex has no neighbour '" << toVertex->key() << "'"
              << std::endl;
    return false;
  }

  bool hasEdge(VertexType toVertex) const
  {
    for (auto& to : *this) {
      if (to.second == toVertex) {
        return true;
      }
    }
    return false;
  }
};


template <typename KeyType, typename CostType>
class Vertex : public BasicVertex<KeyType>
{
 private:
  using Edges = VertexEdges<CostType, Vertex<KeyType, CostType>*>;
  Edges m_edges;


 public:
  Vertex(KeyType s) : BasicVertex<KeyType>(s) {}
  ~Vertex() = default;

  void addEdge(Vertex<KeyType, CostType>* toVertex, const CostType& cost)
  {
    m_edges.addEdge(toVertex, cost);
  }

  void removeEdge(Vertex<KeyType, CostType>* toVertex)
  {
    m_edges.removeEdge(toVertex);
  }

  bool hasEdge(Vertex<KeyType, CostType>* toVertex) const
  {
    return m_edges.hasEdge(toVertex);
  }

  Edges getNeighbors() const { return m_edges; }
};


template <typename KeyType, typename CostType>
class Graph : DefaultGraph<KeyType, Vertex<KeyType, CostType>>
{
 private:
  using VertexType = Vertex<KeyType, CostType>;

  VertexMap<KeyType, VertexType>* m_map;
  AdjacencyMatrix<KeyType, VertexType> m_matrix;


 protected:
  void fromToEdge(VertexType* fromVertex, VertexType* toVertex,
                  const CostType& cost)
  {
    if (m_map->hasVertex(fromVertex) && m_map->hasVertex(toVertex)) {
      fromVertex->addEdge(toVertex, cost);
      m_matrix.update();
    }
  }


 public:
  Graph(VertexType* fromVertex, VertexType* toVertex, const CostType& cost)
      : m_map(new VertexMap<KeyType, VertexType>()),
        m_matrix(AdjacencyMatrix<KeyType, VertexType>(m_map))
  {
    m_map->addVertex(fromVertex);
    m_map->addVertex(toVertex);
    fromVertex->addEdge(toVertex, cost);
    m_matrix.update();
  }
  ~Graph() = default;

  bool addVertex(VertexType* fromVertex, VertexType* toVertex,
                 const CostType& cost)
  {
    if (m_map->addVertex(fromVertex) || m_map->addVertex(toVertex)) {
      fromVertex->addEdge(toVertex, cost);
      m_matrix.update();
      return true;
    }
    return false;
  }

  void addEdge(VertexType* fromVertex, VertexType* toVertex,
               const CostType& cost)
  {
    fromToEdge(fromVertex, toVertex, cost);
    m_matrix.update();
  }

  void removeEdge(VertexType* fromVertex, VertexType* toVertex)
  {
    if (m_map->hasVertex(fromVertex) && m_map->hasVertex(toVertex)) {
      fromVertex->removeEdge(toVertex);
      m_matrix.update();
    }
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
      if (fromVertex->hasEdge(target)) {
        if (!parent) {
          parent = fromVertex;
        }
        else {
          fromVertex->removeEdge(target);
        }
      }
    }

    parent->removeEdge(target);
    for (auto& neighbour : target->getNeighbors()) {
      if (!parent->hasEdge(neighbour.second))
        fromToEdge(parent, neighbour.second, neighbour.first);
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
        int D =
          std::distance(m_map->begin(), m_map->find(neighbour.second->key()));
        if (!visited[D]) {
          visited[D] = true;
          queue.push_back(neighbour.second);
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
      int D =
        std::distance(m_map->begin(), m_map->find(neighbour.second->key()));
      if (!visited[D])
        DFS(visited, neighbour.second);
    }
  }

  void showMatrix()
  {
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

  void print()
  {
    int i = 0;
    for (auto& [keyA, vertexA] : *m_map) {
      if (i == 0) {
        std::cout << "\t";
        for (const auto& [key, _] : *m_map) {
          std::cout << key << "\t";
        }
        std::cout << std::endl;
      }
      std::cout << keyA << "\t";

      for (auto& [keyB, vertexB] : *m_map) {
        if (vertexB->hasEdge(vertexA)) {
          for (auto& neighbour : vertexB->getNeighbors()) {
            if (neighbour.second == vertexA)
              std::cout << neighbour.first;
          }
        }
        else {
          std::cout << "0";
        }
        std::cout << "\t";
        i++;
      }
      std::cout << std::endl;
    }
  }
};
} // namespace graphs