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
  return 0;
}