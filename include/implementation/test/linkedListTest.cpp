#include "../../include/implementation/linkedListImpl.hpp"


int main()
{
  using namespace linked_lists;

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

  {
    LinkedList<int>* list = new LinkedList<int>(new Node<int>(0));
    list->push_front(new Node<int>(1));

    std::cout << "list: " << *list << std::endl;
    std::cout << "head:" << *list->front() << std::endl;
    std::cout << "tail:" << *list->back() << std::endl;
    std::cout << "list size: " << list->size() << std::endl;

    list->push_front(2);
    list->push_back(4);
    list->push_back(new Node<int>(3));
    std::cout << "list: " << *list << std::endl;
    std::cout << "head:" << *list->front() << std::endl;
    std::cout << "tail:" << *list->back() << std::endl;

    list->pop_front();
    list->pop_back();
    std::cout << "list: " << *list << std::endl;
    std::cout << "head:" << *list->front() << std::endl;
    std::cout << "tail:" << *list->back() << std::endl;

    list->insert(5, 100);
    list->insert(5, 2);
    list->insert(new Node<int>(6), 4);
    list->insert(new Node<int>(7), 200);
    list->insert(7, 0);
    std::cout << "list: " << *list << std::endl;
    std::cout << "list size: " << list->size() << std::endl;

    list->erase(100);
    list->erase(3);
    std::cout << "list: " << *list << std::endl;
    std::cout << "list size: " << list->size() << std::endl;
    delete list;
  }

  {
    EdgeNode<std::string, int>* node = new EdgeNode<std::string, int>(
      "A", new EdgeNode<std::string, int>("B"), 1);
    LinkedEdgeList<std::string, int>* list =
      new LinkedEdgeList<std::string, int>(node);

    std::cout << "list: " << *list << std::endl;
    std::cout << "size: " << list->size() << std::endl;
    std::cout << "head:" << *list->front() << std::endl;
    std::cout << "tail:" << *list->back() << std::endl;

    list->push_front("C", 2);
    list->push_front(new EdgeNode<std::string, int>("D", nullptr, 3));
    list->push_back(4, "E");
    list->push_back(5, new EdgeNode<std::string, int>("F"));

    std::cout << "list: " << *list << std::endl;
    std::cout << "size: " << list->size() << std::endl;

    list->pop_front();
    list->pop_back();

    std::cout << "list: " << *list << std::endl;
    std::cout << "size: " << list->size() << std::endl;
    std::cout << "head:" << *list->front() << std::endl;
    std::cout << "tail:" << *list->back() << std::endl;

    list->insert("G", 6, 100);
    list->insert("G", 6, 2);
    list->insert(new EdgeNode<std::string, int>("H", nullptr, 7), 4);

    std::cout << "list: " << *list << std::endl;
    std::cout << "size: " << list->size() << std::endl;

    list->erase(100);
    list->erase(3);
    std::cout << "list: " << *list << std::endl;
    std::cout << "list size: " << list->size() << std::endl;
    delete list;
  }
  return 0;
}