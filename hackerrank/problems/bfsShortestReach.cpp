#include "../../include/implementation/linkedListImpl.hpp"


using namespace helper;


// template <typename T>
// struct Edge
// {
//  private:
//   T m_cost;
//
//  public:
//   Edge(T cost) : m_cost(cost) {};
//   T operator()() { return m_cost; };
// };
//
//
// template <typename LabelType, typename CostType>
// struct Node
// {
//   using L = LabelType;
//   using C = CostType;
//
//  private:
//   std::map<Node<L, C>*, C> m_neighbors;
//   L m_label;
//
//  public:
//   Node(L label) : m_label(label) {};
//   Node(L label, Node<L, C>* node, const C cost) : Node(label)
//   {
//     this->operator()(cost, node);
//   };
//
//   L operator()() { return m_label; };
//   void operator()(const C cost, Node<L, C>* node) { m_neighbors[node] = cost;
//   }; C operator()(Node<L, C>* node) { return m_neighbors[node]; };
// };
//
//
// template <typename T>
// class AdjacencyList
// {
//   using namespace linked_lists;
//
//  private:
//   size_t m_capacity;
//   size_t m_size = 0;
//   std::unordered_map<L, LinkedList<L>> m_list;
//
//  public:
//   AdjacencyList(size_t capacity)
//       : m_capacity(size), m_list(std::vector<linked_lists<T>>(size)) {};
//
//   void addEdge()
// };
//
//
// class AdjacencyMatrix
// {};
//
//
// template <typename LabelType, typename CostType>
// class Graph
// {
//   using L = LabelType;
//   using C = CostType;
//
//  private:
//  public:
//   Graph(size_t numberOfNodes) {}
//
//   void add_edge(L nodeA, L nodeB) {}
//
//   std::vector<C> shortest_reach(L startNode) {}
// };


int main()
{
  using namespace linked_lists;

  // const int numberOfNodes = RandomGenerator<int>(1, 10)();

  // const int numberOfEdges =
  //   RandomGenerator<int>(1, (numberOfNodes * (numberOfNodes - 1)) / 2)();
  // const std::vector<std::vector<int>> edges =
  //   RandomGenerator<int>(1, numberOfNodes)
  //     .randomNdUniqueVector(2, numberOfEdges);

  // print<char[], int>("nodes", numberOfNodes);
  // print<char[], int>("edges", edges);

  // // Create a graph of size n where each edge weight is 6:
  // Graph g(numberOfNodes);
  // for (auto& edge : edges) {
  //   g.add_edge(edge[0], edge[1]);
  // }

  // const int startNode = RandomGenerator<int>(1, numberOfNodes)();
  // print<char[], int>("start node", startNode);
  // std::vector<int> distances = g.shortest_reach(startNode);
  // print<char[], int>("distances", distances);
  return 0;
}