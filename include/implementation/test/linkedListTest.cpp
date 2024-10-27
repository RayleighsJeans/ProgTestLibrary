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
  LinkedList<int>* list = new LinkedList<int>(new Node<int>(0));
  Node<int>* nodeB = new Node<int>(2);
  Node<int>* nodeA = new Node<int>(1, nodeB);
  list->push_front(nodeA);

  std::cout << "list: " << *list << std::endl;
  std::cout << "head:" << *list->front() << std::endl;
  std::cout << "tail:" << *list->back() << std::endl;
  std::cout << "list size: " << list->size() << std::endl;

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