#include <gtest/gtest.h>

#include "../tables/hashTableImpl.hpp"


using namespace linked_lists;
using namespace hash_tables;


constexpr size_t CAPACITY = 5000;


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

unsigned long hash_function(char* str)
{
  unsigned long i = 0;

  for (int j = 0; str[j]; j++)
    i += str[j];

  return i % CAPACITY;
}

TEST_F(TestPrimer, HashTableTest) {}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::AddGlobalTestEnvironment(new TestEnvironment);

  int result = RUN_ALL_TESTS();
  return result;
}