#include "../../include/header.hpp"


using namespace helper;


class Graph
{
 private:
  struct Edge
  {
   private:
    int m_cost;

   public:
    Edge(int cost) : m_cost(cost) {};
    int operator()() { return m_cost; };
  };

  struct Node
  {
   private:
    std::map<Node*, Edge*> m_neighbors;
    int m_label;

   public:
    Node(int label) : m_label(label) {};
    Node(int label, Node* node, Edge* edge) : Node(label)
    {
      this->operator()(edge, node);
    };

    int operator()() { return m_label; };
    void operator()(Edge* edge, Node* node) { m_neighbors[node] = edge; };
    Edge* operator()(Node* node) { return m_neighbors[node]; };

    std::vector<Node*> neighbors()
    {
      std::vector<Node*> list;
      for (auto& [node, edge] : m_neighbors)
        list.push_back(node);
      return list;
    }
  };

  std::map<int, Node*> m_logbook;
  int m_size;

 public:
  Graph(int numberOfNodes) : m_size(numberOfNodes)
  {
    if ((size_t)numberOfNodes > m_logbook.max_size())
      std::cout
        << ">> \033[1;31mOverflow number of requested nodes.\033[0m Max size "
        << m_logbook.max_size() << "." << std::endl;
  }

  void add_edge(int nodeA, int nodeB)
  {
    Node* toNode;
    if (!m_logbook.count(nodeB)) {
      toNode = new Node(nodeB);
      m_logbook[nodeB] = toNode;
    }
    toNode = m_logbook[nodeB];

    Node* fromNode;
    if (!m_logbook.count(nodeA)) {
      fromNode = new Node(nodeA, toNode, new Edge(6));
      m_logbook[nodeA] = fromNode;
    }
    else {
      fromNode = m_logbook[nodeA];
      fromNode->operator()(new Edge(6), toNode);
    }
  }

  std::vector<int> shortest_reach(int startNode)
  {
    std::vector<int> distance;

    if (!m_logbook.count(startNode)) {
      std::cout << ">> \033[1;31mStart node not in graph.\033[0m" << std::endl;
    }
    Node* root = m_logbook[startNode];

    std::map<int, int> reach;

    // std::function<void(const int, Node*)> connectToNode =
    //   [connectToNode, &reach](const int cost, Node* thisNode)
    // {
    //   int name = thisNode->operator()();
    //   if ((!reach.count(thisNode->operator()())) || (cost < reach[name]))
    //     reach[name] = cost;

    //   for (auto neighbor : thisNode->neighbors())
    //     connectToNode(thisNode->operator()(neighbor)->operator()(),
    //     neighbor);
    // };
    connectToNode(reach, 0, root);

    print<char[], int, int>("reach", reach);

    return distance;
  }

 private:
  void connectToNode(std::map<int, int>& reach, const int cost, Node* thisNode)
  {
    int name = thisNode->operator()();
    if ((!reach.count(thisNode->operator()())) || (cost < reach[name]))
      reach[name] = cost;

    for (auto neighbor : thisNode->neighbors())
      connectToNode(reach, cost + thisNode->operator()(neighbor)->operator()(),
                    neighbor);
  }
};


int main()
{

  int numberOfNodes = RandomGenerator<int>(1, 10)();
  int numberOfEdges =
    RandomGenerator<int>(1, (numberOfNodes * (numberOfNodes - 1)) / 2)();
  auto edges = RandomGenerator<int>(1, numberOfNodes)
                 .randomNdUniqueVector(numberOfEdges, 2);

  numberOfNodes = 4;
  numberOfEdges = 2;
  edges = {{1, 2}, {1, 3}, {3, 4}};
  print<char[], int>("edges", edges);

  // Create a graph of size n where each edge weight is 6:
  Graph g(numberOfNodes);
  for (auto& edge : edges) {
    g.add_edge(edge[0], edge[1]);
  }

  std::vector<int> distances =
    // g.shortest_reach(RandomGenerator<int>(1, numberOfNodes)());
    g.shortest_reach(1);
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