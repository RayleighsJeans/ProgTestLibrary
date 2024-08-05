#include "../include/implementation/graphImpl.hpp"
#include "../include/implementation/treeImpl.hpp"


int main()
{
  {
    using namespace trees;
    auto n1 = Node<std::string>("n1", 2);

    auto tree = BasicTree<std::string>(2, "n0");

    std::vector<Node<std::string>*> nodes;
    for (int i = 1; i < 7; i++)
      nodes.push_back(
        new Node<std::string>(std::string("n") + std::to_string(i), 2));
    tree.insertNodes(nodes);

    tree.show();

    // auto tree = trees::BasicTree<int>();
    // auto avl = trees::balanced::AVL<int>();
    // Node *root = NULL;
    // root = insertNode(root, 33);
    // root = insertNode(root, 13);
    // root = insertNode(root, 53);
    // root = insertNode(root, 9);
    // root = insertNode(root, 21);
    // root = insertNode(root, 61);
    // root = insertNode(root, 8);
    // root = insertNode(root, 11);
    // printTree(root, "", true);
    // root = deleteNode(root, 13);
    // cout << "After deleting " << endl;
    // printTree(root, "", true);
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
    // g.removeVertex(v2);
    // g.removeAdj(v3, v4);

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