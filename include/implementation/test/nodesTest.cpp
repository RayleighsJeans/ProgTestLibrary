#include <gtest/gtest.h>

#include "../lists/nodesImpl.hpp"


using namespace linked_lists;


class TestEnvironment : public ::testing::Environment
{
 public:
  TestEnvironment(){};
  ~TestEnvironment() override{};
  void SetUp() override {}
  void TearDown() override {}
};

class TestPrimer : public ::testing::Test
{
 protected:
  TestPrimer(){};
  ~TestPrimer() override{};
  void SetUp() override {}
  void TearDown() override {}
};


TEST_F(TestPrimer, EmptyNodeTest)
{
  EmptyNode<std::string>* node = new EmptyNode<std::string>("foo");
  EXPECT_EQ((*node)(), "foo");

  EmptyNode<std::string> newNode(*node);
  EXPECT_EQ(newNode(), "foo");

  EmptyNode<std::string> newerNode;
  EXPECT_EQ(newerNode(), "");

  newNode("bar");
  EXPECT_EQ(newNode(), "bar");

  node->label("acid");
  EXPECT_EQ(node->label(), "acid");

  EmptyNode<std::string> newestNode(*node);
  EXPECT_EQ(newestNode.label(), "acid");

  std::cout << "newestNode: " << newestNode << std::endl;

  delete node;
}

TEST_F(TestPrimer, NodeTest)
{
  Node<int> nodeB(11);
  Node<int>* nodeA = new Node<int>(10, nodeB);

  EXPECT_EQ((*nodeA)(), 10);
  EXPECT_EQ(nodeA->next()->label(), 11);
  EXPECT_EQ(nodeA->next()->next(), nullptr);

  Node<int> nodeC;
  EXPECT_EQ(nodeC(), int());
  nodeC.label(12);

  nodeA->next(nodeC);
  EXPECT_EQ(nodeA->next()->label(), 12);

  Node<int>* nodeE = new Node<int>(13);
  nodeA->next()->next(nodeE);
  EXPECT_EQ(nodeA->next()->next()->label(), 13);

  nodeE->next(new Node<int>(14));
  EXPECT_EQ(nodeA->next()->next()->next()->label(), 14);

  std::cout << "nodeA: " << *nodeA << std::endl;

  delete nodeA;
}

TEST_F(TestPrimer, EdgeNodeTest)
{
  EdgeNode<std::string, int>* node = new EdgeNode<std::string, int>(
    "foo", new EdgeNode<std::string, int>("bar"), 5);

  EXPECT_EQ((*node)(), "foo");
  EXPECT_EQ(node->next()->label(), "bar");
  EXPECT_EQ(node->edge(), 5);

  (*node)("foobar");
  node->edge(10);
  EXPECT_EQ(node->label(), "foobar");
  EXPECT_EQ(node->next()->label(), "bar");
  EXPECT_EQ(node->edge(), 10);

  EdgeNode<std::string, int> newestNode("override");
  EdgeNode<std::string, int> newerNode("crash", newestNode, 20);

  node->next(newerNode, 15);
  EXPECT_EQ(node->next()->label(), "crash");
  EXPECT_EQ(node->edge(), 15);
  EXPECT_EQ(node->next()->next()->label(), "override");
  EXPECT_EQ(node->next()->edge(), 20);

  node->edge(25);
  EXPECT_EQ(node->edge(), 25);

  EdgeNode<std::string, int> finalNode(*node);
  EXPECT_EQ(finalNode.label(), "foobar");
  EXPECT_EQ(finalNode.next(), node->next());
  EXPECT_EQ(finalNode.edge(), 25);

  delete node;
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::AddGlobalTestEnvironment(new TestEnvironment);

  int result = RUN_ALL_TESTS();
  return result;
}