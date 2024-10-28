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


#define EXPECT_EQ(x, y)                                            \
  {                                                                \
    if (true)                                                      \
      std::cout << "L:" << __LINE__ << " | x:" << x << ", y:" << y \
                << std::endl;                                      \
    assert(x == y);                                                \
  }


int main()
{
  std::cout << ">> This does nothing." << std::endl;

  if (false) {
    using namespace linked_lists;
    using NodePtr = std::shared_ptr<Node<int>>;

    NodePtr nodeC = std::make_shared<Node<int>>(2);
    NodePtr nodeB = std::make_shared<Node<int>>(1, nodeC);
    NodePtr nodeD = std::make_shared<Node<int>>(3, nodeB);
    LinkedList<int>* newList = new LinkedList<int>(nodeD);

    EXPECT_EQ(newList->size(), 3);
    EXPECT_EQ(newList->front()->label(), 3);
    EXPECT_EQ(newList->back()->label(), 2);

    delete newList;

    NodePtr nodeA = std::make_shared<Node<int>>(0);
    LinkedList<int>* list = new LinkedList<int>(nodeA);
    list->push_front(nodeB);

    EXPECT_EQ(list->size(), 3);
    EXPECT_EQ(list->front()->label(), 1);
    EXPECT_EQ(list->front()->next()->label(), 2);
    EXPECT_EQ(list->back()->label(), 0);

    NodePtr nodeE = std::make_shared<Node<int>>(6);
    NodePtr nodeF = std::make_shared<Node<int>>(5, nodeE);
    list->push_back(std::make_shared<Node<int>>(4));
    list->push_back(nodeF);

    EXPECT_EQ(list->size(), 6);
    EXPECT_EQ(list->back()->label(), 6);

    list->pop_front();
    list->pop_back();

    EXPECT_EQ(list->size(), 4);
    EXPECT_EQ(list->front()->label(), 2);
    EXPECT_EQ(list->front()->next()->label(), 0);
    EXPECT_EQ(list->back()->label(), 5);

    list->insert(5, 100);
    list->insert(5, 2);
    list->insert(std::make_shared<Node<int>>(6), 4);
    list->insert(std::make_shared<Node<int>>(7), 200);
    list->insert(7, 0);

    EXPECT_EQ(list->size(), 7);
    EXPECT_EQ(list->front()->label(), 7);
    EXPECT_EQ(list->front()->next()->next()->next()->label(), 5);
    EXPECT_EQ(list->find(nodeA), 2);
    EXPECT_EQ(list->find(4), 4);

    list->erase((size_t)100);
    list->erase((size_t)3);
    list->erase((int)5);
    list->erase(nodeA);

    EXPECT_EQ(list->size(), 4);
    EXPECT_EQ(list->front()->next()->next()->label(), 4);
    EXPECT_EQ(list->at((size_t)3)->label(), 6);

    delete list;
  }

  {
    using namespace linked_lists;
    std::shared_ptr<Node<int>> nodeB = std::make_shared<Node<int>>(11);
    std::shared_ptr<Node<int>> nodeA = std::make_shared<Node<int>>(10, nodeB);

    EXPECT_EQ((*nodeA)(), 10);
    EXPECT_EQ(nodeA->next()->label(), 11);
    EXPECT_EQ(nodeA->next()->next(), nullptr);

    std::shared_ptr<Node<int>> nodeC = std::make_shared<Node<int>>();
    EXPECT_EQ((*nodeC)(), int());
    nodeC->label(12);

    nodeA->next(nodeC);
    EXPECT_EQ(nodeA->next()->label(), 12);

    std::shared_ptr<Node<int>> nodeE = std::make_shared<Node<int>>(13);
    nodeA->next()->next(nodeE);
    EXPECT_EQ(nodeA->next()->next()->label(), 13);

    nodeE->next(std::make_shared<Node<int>>(14));
    EXPECT_EQ(nodeA->next()->next()->next()->label(), 14);

    std::shared_ptr<Node<int>> nodeD = std::make_shared<Node<int>>(15);
    nodeE->next()->next(nodeD);
    EXPECT_EQ(nodeA->next()->next()->next()->next()->label(), 15);

    std::cout << "nodeA: " << *nodeA << std::endl;
  }

  return 0;
}