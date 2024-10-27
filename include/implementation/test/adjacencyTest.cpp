#include <gtest/gtest.h>

#include "../graphs/adjacencyImpl.hpp"
#include "../graphs/vertexImpl.hpp"


using namespace graphs;


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


TEST_F(TestPrimer, BasicVertexTest)
{
  AdjacencyList<BasicVertex<std::string>, std::string>* list =
    new AdjacencyList<BasicVertex<std::string>, std::string>(
      new BasicVertex<std::string>("foo"));

  list->put(new BasicVertex<std::string>("bar"));
  list->put("acid");

  delete list;
}

TEST_F(TestPrimer, EdgeVertexTest)
{
  AdjacencyEdgeList<EdgeVertex<std::string, int>, std::string, int>* list =
    new AdjacencyEdgeList<EdgeVertex<std::string, int>, std::string, int>(
      new EdgeVertex<std::string, int>());

  // list->put(5, new EdgeVertex<std::string, int>("bar"));
  // list->put(10, "acid");

  delete list;
}


int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::AddGlobalTestEnvironment(new TestEnvironment);

  int result = RUN_ALL_TESTS();
  return result;
}