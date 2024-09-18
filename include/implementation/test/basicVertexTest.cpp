#include "../../header.hpp"
#include "../graphs/vertexImpl.hpp"


using namespace helper;
using namespace graphs;


int main()
{
  {
    BasicVertex<std::string>* vertex = new BasicVertex<std::string>("foo");

    std::cout << "vertex:" << *vertex << std::endl;
    std::cout << "key:" << vertex->key() << std::endl;
    std::cout << "label:" << (*vertex)() << std::endl;

    (*vertex)("bar");

    std::cout << "vertex:" << *vertex << std::endl;
    std::cout << "label:" << (*vertex)() << std::endl;
    delete vertex;
  }

  {
    Vertex<std::string>* vertex = new Vertex<std::string>("foo");
    Vertex<std::string>* node = new Vertex<std::string>("bar");

    vertex->connect(node);
    vertex->connect("acid");
    vertex->connect("burn");
    vertex->connect("crash");
    vertex->connect("override");
    std::cout << "vertex: " << *vertex << std::endl;

    bool res = vertex->connect(node);
    std::cout << "add node: '" << res << "'" << std::endl;
    res = vertex->find(node);
    std::cout << "find (node): '" << res << "'" << std::endl;

    std::cout << "remove node: ";
    vertex->remove(node);
    std::cout << std::endl << "remove 'acid': ";
    vertex->remove("acid");
    std::cout << std::endl << "remove node: ";
    vertex->remove(node);

    std::cout << "vertex edges:" << vertex->edges() << std::endl;
    delete vertex;
  }

  {
    EdgeVertex<std::string, int>* vertex =
      new EdgeVertex<std::string, int>("foo");
    EdgeVertex<std::string, int>* node =
      new EdgeVertex<std::string, int>("bar");

    delete vertex;
  }

  return 0;
}