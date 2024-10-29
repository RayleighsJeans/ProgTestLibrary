#include <gtest/gtest.h>

#include "../lists/linkedListImpl.hpp"


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

TEST_F(TestPrimer, LinkedListTest)
{
  std::shared_ptr<Node<int>> nodeC = std::make_shared<Node<int>>(2);
  std::shared_ptr<Node<int>> nodeB = std::make_shared<Node<int>>(1, nodeC);
  std::shared_ptr<Node<int>> nodeD = std::make_shared<Node<int>>(3, nodeB);
  LinkedList<int>* newList = new LinkedList<int>(nodeD);

  EXPECT_EQ(newList->size(), 3);
  EXPECT_EQ(newList->front()->label(), 3);
  EXPECT_EQ(newList->back()->label(), 2);

  delete newList;

  std::shared_ptr<Node<int>> nodeA = std::make_shared<Node<int>>(0);
  LinkedList<int>* list = new LinkedList<int>(nodeA);
  list->push_front(nodeB);

  EXPECT_EQ(list->size(), 3);
  EXPECT_EQ(list->front()->label(), 1);
  EXPECT_EQ(list->front()->next()->label(), 2);
  EXPECT_EQ(list->back()->label(), 0);

  std::shared_ptr<Node<int>> nodeE = std::make_shared<Node<int>>(6);
  std::shared_ptr<Node<int>> nodeF = std::make_shared<Node<int>>(5, nodeE);
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

TEST_F(TestPrimer, LinkedEdgeListTest)
{
  std::shared_ptr<EdgeNode<std::string, int>> nodeB(
    new EdgeNode<std::string, int>("B"));
  std::shared_ptr<EdgeNode<std::string, int>> nodeA =
    std::make_shared<EdgeNode<std::string, int>>("A", nodeB, 1);
  LinkedEdgeList<std::string, int>* list =
    new LinkedEdgeList<std::string, int>(nodeA);

  EXPECT_EQ(list->size(), 2);
  EXPECT_EQ(list->front()->label(), "A");
  EXPECT_EQ(list->front()->edge(), 1);
  EXPECT_EQ(list->front()->next()->label(), "B");
  EXPECT_EQ(list->back()->label(), "B");
  EXPECT_EQ(list->back()->next(), nullptr);
  EXPECT_EQ(list->back()->edge(), 0);

  list->push_front("C", 2);
  list->push_front(
    std::make_shared<EdgeNode<std::string, int>>("D", nullptr, 3));
  list->push_back(4, "E");
  list->push_back(5, std::make_shared<EdgeNode<std::string, int>>("F"));

  EXPECT_EQ(list->size(), 6);
  EXPECT_EQ(list->front()->label(), "D");
  EXPECT_EQ(list->front()->edge(), 3);
  EXPECT_EQ(list->front()->next()->label(), "C");
  EXPECT_EQ(list->back()->label(), "F");

  list->pop_front();
  list->pop_back();

  EXPECT_EQ(list->size(), 4);
  EXPECT_EQ(list->front()->label(), "C");
  EXPECT_EQ(list->front()->edge(), 2);
  EXPECT_EQ(list->front()->next()->label(), "A");
  EXPECT_EQ(list->back()->label(), "E");
  EXPECT_EQ(list->back()->next(), nullptr);
  EXPECT_EQ(list->back()->edge(), 0);

  list->insert("G", 6, 100);
  list->insert("G", 6, 2);
  list->insert(std::make_shared<EdgeNode<std::string, int>>("H", nullptr, 7),
               4);

  EXPECT_EQ(list->size(), 6);
  EXPECT_EQ(list->back()->label(), "H");
  EXPECT_EQ(list->back()->next(), nullptr);
  EXPECT_EQ(list->back()->edge(), 7);
  EXPECT_EQ(list->at((size_t)2)->label(), "G");
  EXPECT_EQ(list->at((size_t)2)->edge(), 6);
  EXPECT_EQ(list->at((size_t)2)->next()->label(), "B");

  list->erase(100);
  list->erase(3);

  EXPECT_EQ(list->size(), 5);
  EXPECT_EQ(list->at((size_t)2)->next()->label(), "E");
  EXPECT_EQ(list->at((size_t)3)->label(), "E");
  EXPECT_EQ(list->at((size_t)3)->edge(), 0);
  EXPECT_EQ(list->at((size_t)3)->next()->label(), "H");

  auto edgeTo = list->edgeTo(nodeB);
  EXPECT_FALSE(edgeTo.has_value());

  edgeTo = list->edgeTo("G");
  EXPECT_TRUE(edgeTo.has_value());
  EXPECT_EQ(edgeTo.value(), 1);

  delete list;
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::AddGlobalTestEnvironment(new TestEnvironment);

  int result = RUN_ALL_TESTS();
  return result;
}