#include "lists/linkedListImpl.hpp"
#include "lists/nodesImpl.hpp"

#include "graphs/adjacencyImpl.hpp"
#include "graphs/vertexImpl.hpp"
// #include "graphs/basicGraphImpl.hpp"
// #include "graphs/graphImpl.hpp"

// #include "tables/hashTableImpl.hpp"

// #include "trees/basicTreeImpl.hpp"
// #include "trees/treeAVLImpl.hpp"

#include <assert.h>
#include <iostream>


#define EXPECT_EQ(x, y)                                                        \
  {                                                                            \
    std::cout << "L:" << __LINE__ << " | x:" << x << ", y:" << y << std::endl; \
    assert(x == y);                                                            \
  }


int main()
{
  std::cout << ">> This does nothing." << std::endl;

  {
    using namespace linked_lists;

    Node<int>* nodeA = new Node<int>(0);
    LinkedList<int>* list = new LinkedList<int>(nodeA);
    Node<int>* nodeC = new Node<int>(2);
    Node<int>* nodeB = new Node<int>(1, nodeC);
    list->push_front(nodeB);

    // std::cout << "list: " << *list << std::endl;
    // std::cout << "head:" << *list->front() << std::endl;
    // std::cout << "tail:" << *list->back() << std::endl;
    // std::cout << "list size: " << list->size() << std::endl;

    // std::cout << "head:" << *list->front() << std::endl;
    // std::cout << "tail:" << *list->back() << std::endl;
    // std::cout << "list size: " << list->size() << std::endl;

    // list->push_front(2);
    // list->push_front(new Node<int>(3));
    // list->push_back(4);
    // list->push_back(new Node<int>(3));
    // std::cout << "list: " << *list << std::endl;
    // std::cout << "head:" << *list->front() << std::endl;
    // std::cout << "tail:" << *list->back() << std::endl;

    // list->pop_front();
    // list->pop_back();
    // std::cout << "list: " << *list << std::endl;
    // std::cout << "head:" << *list->front() << std::endl;
    // std::cout << "tail:" << *list->back() << std::endl;

    // list->insert(5, 100);
    // list->insert(5, 2);
    // list->insert(new Node<int>(6), 4);
    // list->insert(new Node<int>(7), 200);
    // list->insert(7, 0);
    // std::cout << "list: " << *list << std::endl;
    // std::cout << "list size: " << list->size() << std::endl;

    // std::cout << "find node " << *node << " = " << list->find(node) <<
    // std::endl; std::cout << "find label 4 "
    //           << " = " << list->find((int)4) << std::endl;

    // list->erase((size_t)100);
    // list->erase((size_t)3);
    // list->erase((int)5);
    // list->erase(node);

    // std::cout << "list at 3: " << *list->at((size_t)3) << std::endl;
    // std::cout << "list: " << *list << std::endl;
    // std::cout << "list size: " << list->size() << std::endl;

    delete list;
  }

  return 0;
}