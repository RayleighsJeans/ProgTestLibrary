#include <gtest/gtest.h>

#include "../lists/nodesImpl.hpp"


using namespace linked_lists;


class TestEnvironment : public ::testing::Environment
{
 public:
  TestEnvironment() {};
  ~TestEnvironment() override {};
  void SetUp() override {}
  void TearDown() override {}
};

class TestPrimer : public ::testing::Test
{
 protected:
  TestPrimer() {};
  ~TestPrimer() override {};
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

TEST_F(TestPrimer, EdgeNodeTest)
{
  EdgeNode<std::string, int>* node = new EdgeNode<std::string, int>(
    "foo", std::make_shared<EdgeNode<std::string, int>>("bar"), 5);

  EXPECT_EQ((*node)(), "foo");
  EXPECT_EQ(node->next()->label(), "bar");
  EXPECT_EQ(node->edge(), 5);

  (*node)("foobar");
  node->edge(10);
  EXPECT_EQ(node->label(), "foobar");
  EXPECT_EQ(node->next()->label(), "bar");
  EXPECT_EQ(node->edge(), 10);

  std::shared_ptr<EdgeNode<std::string, int>> newestNode =
    std::make_shared<EdgeNode<std::string, int>>("override");
  std::shared_ptr<EdgeNode<std::string, int>> newerNode =
    std::make_shared<EdgeNode<std::string, int>>("crash", newestNode, 20);

  node->next(newerNode, 15);
  EXPECT_EQ(node->next()->label(), "crash");
  EXPECT_EQ(node->edge(), 15);
  EXPECT_EQ(node->next()->next()->label(), "override");
  EXPECT_EQ(node->next()->edge(), 20);

  std::shared_ptr<EdgeNode<std::string, int>> nodePtr =
    std::make_shared<EdgeNode<std::string, int>>("burn");
  node->next()->next(nodePtr, 30);

  node->edge(25);
  EXPECT_EQ(node->edge(), 25);

  EdgeNode<std::string, int> finalNode(*node);
  EXPECT_EQ(finalNode.label(), "foobar");
  EXPECT_EQ(finalNode.next(), node->next());
  EXPECT_EQ(finalNode.edge(), 25);
  EXPECT_EQ(finalNode.next()->next()->label(), "burn");
  EXPECT_EQ(finalNode.next()->edge(), 30);
}

TEST_F(TestPrimer, DoubleNodeTest)
{
  std::shared_ptr<DoubleNode<int>> nodeC =
    std::make_shared<DoubleNode<int>>(12);
  std::shared_ptr<DoubleNode<int>> nodeB = std::make_shared<DoubleNode<int>>(
    11, std::make_shared<DoubleNode<int>>(13), nullptr);
  std::shared_ptr<DoubleNode<int>> nodeA =
    std::make_shared<DoubleNode<int>>(10, nodeB, nodeC);
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::AddGlobalTestEnvironment(new TestEnvironment);

  int result = RUN_ALL_TESTS();
  return result;
}