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

#define EXPECT_FALSE(x)  \
  {                      \
    EXPECT_EQ(x, false); \
  }

#define EXPECT_TRUE(x)  \
  {                     \
    EXPECT_EQ(x, true); \
  }

int main()
{
  std::cout << ">> This does nothing." << std::endl;

  {
    using namespace linked_lists;

    std::shared_ptr<DoubleNode<int>> nodeC =
      std::make_shared<DoubleNode<int>>(12);
    std::shared_ptr<DoubleNode<int>> nodeB =
      std::make_shared<DoubleNode<int>>(11);
    std::shared_ptr<DoubleNode<int>> nodeA =
      std::make_shared<DoubleNode<int>>(10);

    nodeA->next(nodeB);
    nodeA->previous(nodeC);

    std::cout << "double nodeA: " << *nodeA << std::endl;
    std::cout << "double nodeB: " << *nodeB << std::endl;
    std::cout << "double nodeC: " << *nodeC << std::endl;

    EXPECT_EQ(nodeA->next()->label(), 11);
    EXPECT_EQ(nodeB->next(), nullptr);
    EXPECT_EQ(nodeC->next()->label(), 10);
  }

  return 0;
}