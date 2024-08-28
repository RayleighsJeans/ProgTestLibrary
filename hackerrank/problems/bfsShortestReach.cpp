#include "../../include/header.hpp"


using namespace helper;


struct Edge
{
 private:
  int m_cost;

 public:
  Edge(int cost) : m_cost(cost){};
  int operator()() { return m_cost; };
};


struct Node
{
 private:
  std::map<Node*, Edge*> m_neighbors;
  int m_label;

 public:
  Node(int label) : m_label(label){};
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


class Graph
{
 private:
  std::vector<std::vector<int>> m_matrix;
  std::map<int, Node*> m_logbook;
  int m_size;


  void connectToNode(std::map<int, int>& reach, int cost, Node* thisNode,
                     Node* parentNode)
  {
    int name = thisNode->operator()();

    if ((!reach.count(thisNode->operator()())) || (cost < reach[name]))
      reach[name] = cost;

    for (auto neighbor : thisNode->neighbors())
      if (neighbor != parentNode)
        connectToNode(reach,
                      cost + thisNode->operator()(neighbor)->operator()(),
                      neighbor, thisNode);
  };

 public:
  Graph(int numberOfNodes) : m_size(numberOfNodes)
  {
    if ((size_t)numberOfNodes > m_logbook.max_size())
      std::cout
        << ">> \033[1;31mOverflow number of requested nodes.\033[0m Max size "
        << m_logbook.max_size() << "." << std::endl;
  }

  void debug()
  {
    for (auto [label, node] : m_logbook) {
      std::vector<int> neighbors;
      for (auto adj : node->neighbors())
        neighbors.push_back(adj->operator()());

      std::cout << ">> this node " << label << ", neighbors : ";
      print<int>(neighbors);
    }
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
      return distance;
    }

    Node* root = m_logbook[startNode];
    std::map<int, int> reach;

    connectToNode(reach, 0, root, nullptr);

    for (auto [label, node] : m_logbook) {
      if (label == root->operator()())
        continue;
      if (!reach.count(node->operator()()))
        distance.push_back(-1);
      else
        distance.push_back(reach[node->operator()()]);
    }
    return distance;
  }
};


int main()
{
  const int numberOfNodes = RandomGenerator<int>(1, 10)();
  const int numberOfEdges =
    RandomGenerator<int>(1, (numberOfNodes * (numberOfNodes - 1)) / 2)();
  const std::vector<std::vector<int>> edges =
    RandomGenerator<int>(1, numberOfNodes)
      .randomNdUniqueVector(2, numberOfEdges);

  print<char[], int>("nodes", numberOfNodes);
  print<char[], int>("edges", edges);

  // Create a graph of size n where each edge weight is 6:
  Graph g(numberOfNodes);
  for (auto& edge : edges) {
    g.add_edge(edge[0], edge[1]);
  }

  const int startNode = RandomGenerator<int>(1, numberOfNodes)();
  print<char[], int>("start node", startNode);
  std::vector<int> distances = g.shortest_reach(startNode);
  print<char[], int>("distances", distances);
  return 0;
}