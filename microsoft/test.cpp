#include "../include/implementation/graphImpl.hpp"
#include "../include/implementation/treeImpl.hpp"


int main()
{
  if (false) {
    using namespace trees;
    auto tree = binary::balanced::AVLTree<std::string>("n0");

    std::vector<Node<std::string>*> nodes;
    for (int i = 1; i < 5; i++)
      nodes.push_back(new binary::BinaryNode<std::string>(std::string("n") +
                                                          std::to_string(i)));
    tree.insertNodes(nodes);
    tree.show();
    tree.removeNode(tree.getNode("n0"), tree.getNode("n1"));
    tree.show();
  }

  if (true) {
    using namespace trees;
    auto n1 = Node<std::string>("n1", 2);

    auto tree = BasicTree<std::string>(2, "n0");

    std::vector<Node<std::string>*> nodes;
    for (int i = 1; i < 10; i++)
      nodes.push_back(
        new Node<std::string>(std::string("n") + std::to_string(i), 2));
    tree.insertNodes(nodes);
    tree.balanceTree();
    tree.show();

    tree.removeNode(tree.getNode("n4"));
    tree.show();

    tree.DFS();
    tree.BFS();
  }

  if (false) {
    using namespace graphs;
    auto v1 = new BasicVertex<std::string>("v1");
    auto v2 = new BasicVertex<std::string>("v2");
    auto v3 = new BasicVertex<std::string>("v3");
    auto v4 = new BasicVertex<std::string>("v4");

    auto g = BasicGraph<std::string>(v1, v2);
    g.addVertex(v2, v3);
    g.addVertex(v2, v4);
    g.addAdj(v1, v4);
    g.addAdj(v3, v4);
    g.removeVertex(v2);
    g.removeAdj(v3, v4);

    g.print();

    g.BFS();
    g.DFS();
  }

  if (false) {
    using namespace graphs;
    auto v1 = new Vertex<std::string, int>("v1");
    auto v2 = new Vertex<std::string, int>("v2");
    auto v3 = new Vertex<std::string, int>("v3");
    auto v4 = new Vertex<std::string, int>("v4");

    auto g = Graph<std::string, int>(v1, v2, 5);
    g.addVertex(v2, v3, 10);
    g.addVertex(v2, v4, 25);
    g.addEdge(v1, v4, 15);
    g.addEdge(v3, v4, 20);
    g.removeVertex(v2);
    g.removeEdge(v3, v4);

    g.print();

    g.BFS();
    g.DFS();
  }

  return 0;
}