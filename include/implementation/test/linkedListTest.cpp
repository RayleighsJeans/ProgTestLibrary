#include <gtest/gtest.h>

#include "../lists/linkedListImpl.hpp"


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

// TEST_F(TestPrimer, LinkedEdgeListTest)
// {
//   EdgeNode<std::string, int>* node =
//     new EdgeNode<std::string, int>("A", new EdgeNode<std::string, int>("B"),
//     1);
//   LinkedEdgeList<std::string, int>* list =
//     new LinkedEdgeList<std::string, int>(node);

//   std::cout << "list: " << *list << std::endl;
//   std::cout << "size: " << list->size() << std::endl;
//   std::cout << "head:" << *list->front() << std::endl;
//   std::cout << "tail:" << *list->back() << std::endl;

//   list->push_front("C", 2);
//   list->push_front(new EdgeNode<std::string, int>("D", nullptr, 3));
//   list->push_back(4, "E");
//   list->push_back(5, new EdgeNode<std::string, int>("F"));

//   std::cout << "list: " << *list << std::endl;
//   std::cout << "size: " << list->size() << std::endl;

//   list->pop_front();
//   list->pop_back();

//   std::cout << "list: " << *list << std::endl;
//   std::cout << "size: " << list->size() << std::endl;
//   std::cout << "head:" << *list->front() << std::endl;
//   std::cout << "tail:" << *list->back() << std::endl;

//   list->insert("G", 6, 100);
//   list->insert("G", 6, 2);
//   list->insert(new EdgeNode<std::string, int>("H", nullptr, 7), 4);

//   std::cout << "list: " << *list << std::endl;
//   std::cout << "size: " << list->size() << std::endl;

//   list->erase(100);
//   list->erase(3);
//   std::cout << "list: " << *list << std::endl;
//   std::cout << "list size: " << list->size() << std::endl;

//   std::cout << "edge to node: " << list->edgeTo(node).value() << std::endl;
//   std::cout << "edge to '(G)':" << list->edgeTo("G").value() << std::endl;
//   delete list;
// }

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::AddGlobalTestEnvironment(new TestEnvironment);

  int result = RUN_ALL_TESTS();
  return result;
}