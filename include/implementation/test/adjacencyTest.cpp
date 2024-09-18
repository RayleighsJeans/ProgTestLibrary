#include "../../header.hpp"
#include "../graphs/adjacencyImpl.hpp"
#include "../graphs/vertexImpl.hpp"


using namespace helper;
using namespace graphs;


int main()
{
  {
    AdjacencyList<BasicVertex<std::string>, std::string>* list =
      new AdjacencyList<BasicVertex<std::string>, std::string>(
        new BasicVertex<std::string>("foo"));

    list->put(new BasicVertex<std::string>("bar"));
    std::cout << "list: " << *list << std::endl;
    list->put("acid");
    std::cout << "list: " << *list << std::endl;

    delete list;
  }

  {
    AdjacencyEdgeList<EdgeVertex<std::string, int>, std::string, int>* list =
      new AdjacencyEdgeList<EdgeVertex<std::string, int>, std::string, int>(
        new EdgeVertex<std::string, int>());

    // AdjacencyEdgeList<BasicVertex<std::string>, std::string, int>* list =
    //   new AdjacencyEdgeList<BasicVertex<std::string>, std::string, int>(
    //     new BasicVertex<std::string>("foo"));

    // list->put(5, new BasicVertex<std::string>("bar"));
    // std::cout << "list: " << *list << std::endl;
    // list->put(10, "acid");
    // std::cout << "list: " << *list << std::endl;

    delete list;
  }

  return 0;
}