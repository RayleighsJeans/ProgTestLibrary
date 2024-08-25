#include "../../include/header.hpp"


using namespace helper;


class Graph
{
 public:
  Graph(int numberOfNodes) {}

  void add_edge(int nodeA, int nodeB) {}

  std::vector<int> shortest_reach(int startNode) {}
};


int main()
{
  const int numberOfNodes = RandomGenerator<int>(1, 10)();
  const int numberOfEdges =
    RandomGenerator<int>(1, numberOfNodes * (numberOfNodes - 1) / 2)();
  auto edges = RandomGenerator<int>(1, numberOfNodes)
                 .randomNdUniqueVector(numberOfEdges, 2);

  print<char[], int>("edges", edges);

  // Create a graph of size n where each edge weight is 6:
  Graph g(numberOfNodes);
  for (auto& edge : edges) {
    g.add_edge(edge[0], edge[1]);
  }

  std::vector<int> distances =
    g.shortest_reach(RandomGenerator<int>(1, numberOfNodes)());
  print<char[], int>("distances", distances);


  //   for (int i = 0; i < distances.size(); i++) {
  //     if (i != startId) {
  //       std::cout << distances[i] << " ";
  //     }
  //   }
  //   std::cout << std::endl;
  // }

  return 0;
}