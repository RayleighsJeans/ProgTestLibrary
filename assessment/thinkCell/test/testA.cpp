#include <gtest/gtest.h>

#include <iostream>
#include <random>
#include <string>

#include "../../../include/distributions.hpp"
#include "../include/interval_map.hpp"

using TypeK = int;
using TypeV = char;

using Tuple = std::pair<std::pair<TypeK, TypeK>, TypeV>;

using namespace think_cell;
using K = KeyType<TypeK>;
using V = ValueType<TypeV>;


const V DefaultCharacter = V('~');

constexpr int MaxAttempts = 10000;
constexpr int MaxNumeral = 32;
constexpr int MaxKey = MaxAttempts;


class TestEnvironment : public ::testing::Environment
{
 public:
  static interval_map<TypeK, TypeV>* m_intervalMap;

  TestEnvironment(){};
  ~TestEnvironment() { delete m_intervalMap; };
};
interval_map<TypeK, TypeV>* TestEnvironment::m_intervalMap =
  new interval_map<TypeK, TypeV>(DefaultCharacter);


class TestPrimer : public ::testing::Test
{
 private:
  helper::RandomDistribution<int> m_keyDist;
  helper::RandomDistribution<int> m_valueDist;
  std::mt19937 m_generator;

 protected:
  TestPrimer()
      : m_keyDist(helper::RandomDistribution<int>(-MaxAttempts, MaxAttempts)),
        m_valueDist(helper::RandomDistribution<int>(-MaxNumeral, MaxNumeral)),
        m_generator(std::mt19937((std::random_device())())){};
  ~TestPrimer() = default;

  void message(const int atp, const Tuple tuple, const V mapValue) const
  {
    const auto diff = fabs(tuple.first.second - tuple.first.first);
    std::cout << atp << " [" << tuple.first.first << ", " << tuple.first.second
              << "] " << diff << " " << tuple.second << " (" << mapValue << ")"
              << "\n";
  }

  int nextKey() { return m_keyDist(m_generator); }

  int nextValue() { return m_valueDist(m_generator); }

  Tuple tuple()
  {
    Tuple t;
    t.first.first = nextKey();
    t.first.second = nextKey();
    t.second = 'a' + nextValue() % 26;
    return t;
  };

  void print() { TestEnvironment::m_intervalMap->print(); }

  bool validate() { return TestEnvironment::m_intervalMap->validate(); }

  void assign(const Tuple tuple)
  {
    TestEnvironment::m_intervalMap->assign(
      K(tuple.first.first), K(tuple.first.second), V(tuple.second));
  }

  void assignTest(const Tuple tuple)
  {
    TestEnvironment::m_intervalMap->assignTest(
      K(tuple.first.first), K(tuple.first.second), V(tuple.second));
  }

  V get(const K it) const
  {
    return TestEnvironment::m_intervalMap->operator[](it);
  }
};

TEST_F(TestPrimer, Test)
{
  for (int n = 0; n < MaxAttempts; ++n) {
    Tuple entry = tuple();
    const V mapValue = get(entry.first.second);
    if (false)
      message(n, entry, mapValue);
    assignTest(entry);
    EXPECT_TRUE(validate()) << *TestEnvironment::m_intervalMap;

    if (entry.first.first < entry.first.second) {
      for (int l = entry.first.first; l < entry.first.second; l++)
        EXPECT_EQ(get(l), entry.second) << *TestEnvironment::m_intervalMap;

      if (mapValue.m_value != entry.second) {
        EXPECT_NE(get(entry.first.second), entry.second)
          << *TestEnvironment::m_intervalMap;
      }
    }

    EXPECT_EQ(get(-MaxKey - 1).m_value, '~') << *TestEnvironment::m_intervalMap;
    EXPECT_EQ(get(MaxKey + 1).m_value, '~') << *TestEnvironment::m_intervalMap;
  }
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::AddGlobalTestEnvironment(new TestEnvironment);

  int result = RUN_ALL_TESTS();
  std::cout << ">> final map: " << *TestEnvironment::m_intervalMap;
  return result;
}