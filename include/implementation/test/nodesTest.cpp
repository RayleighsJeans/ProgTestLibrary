#include "../../header.hpp"
#include "../lists/nodesImpl.hpp"


using namespace helper;
using namespace linked_lists;


int main()
{
  {
    EmptyNode<std::string>* node = new EmptyNode<std::string>("foo");
    std::cout << "node:" << *node << std::endl;
    std::cout << "label:" << (*node)() << std::endl;

    (*node)("bar");

    std::cout << "node:" << *node << std::endl;
    std::cout << "label:" << (*node)() << std::endl;

    node->label("acid");

    std::cout << "node:" << *node << std::endl;
    std::cout << "label:" << (*node)() << std::endl;
    std::cout << "label:" << node->label() << std::endl;

    delete node;
  }

  {
    Node<int>* foo = new Node<int>(0, new Node<int>(3));
    std::cout << "this: " << *foo << std::endl;
    std::cout << "label: " << (*foo)() << std::endl;
    std::cout << "next: " << (*foo->next())() << std::endl;

    (*foo)(3);
    foo->next(new Node<int>(5));

    std::cout << "this: " << *foo << std::endl;
    std::cout << "label: " << (*foo)() << std::endl;
    std::cout << "next: " << (*foo->next())() << std::endl;

    delete foo;
  }

  {
    EdgeNode<std::string, int>* foo = new EdgeNode<std::string, int>(
      "foo", new EdgeNode<std::string, int>("bar"), 5);

    std::cout << "this: " << *foo << std::endl;
    std::cout << "label: " << (*foo)() << std::endl;
    std::cout << "next: " << (*foo->next())() << std::endl;
    std::cout << "edge: " << foo->edge() << std::endl;

    (*foo)("foobar");
    foo->edge(10);
    std::cout << "this: " << *foo << std::endl;
    foo->next(new EdgeNode<std::string, int>("acid"), 10);
    std::cout << "next: " << (*foo->next())() << std::endl;

    std::cout << "edge: " << foo->edge() << std::endl;
    foo->edge(15);
    std::cout << "edge: " << foo->edge() << std::endl;

    std::cout << "this: " << *foo << std::endl;
    delete foo;
  }

  return 0;
}