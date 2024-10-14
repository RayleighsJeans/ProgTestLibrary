#include <gtest/gtest.h>

#include <iostream>

#include "../include/interval_map.hpp"

using TypeK = int;
using TypeV = char;

using namespace think_cell;

using K = KeyType<TypeK>;
using V = ValueType<TypeV>;


struct Predictions
{
 public:
  TypeK m_pos;
  TypeV m_label;
};

struct Settings
{
 public:
  TypeK m_L;
  TypeK m_R;
  TypeV m_label;
};

class TestPrimer : public ::testing::Test
{
 public:
  interval_map<K, V> m_intervalMap;

 protected:
  TestPrimer() : m_intervalMap(interval_map<K, V>(V('A'))){};
  ~TestPrimer() = default;

  void print() { m_intervalMap.print(); }

  bool validate() { return m_intervalMap.validate(); }

  void assign(const Settings set)
  {
    m_intervalMap.assign(K(set.m_L), K(set.m_R), V(set.m_label));
  }

  void assignTest(const Settings set)
  {
    m_intervalMap.assignTest(K(set.m_L), K(set.m_R), V(set.m_label));
  }

  V get(const K it) const { return m_intervalMap[it].m_value; }

  void setIntervals(const Settings sets[], const int N)
  {
    for (int i = 0; i < N; i++)
      assignTest(sets[i]);
  }

  void checkIntervals(const Predictions expectations[], const int N)
  {
    for (int i = 0; i < N; i++)
      EXPECT_EQ(m_intervalMap[K(expectations[i].m_pos)].m_value,
                expectations[i].m_label)
        << m_intervalMap;
  }
}; // class TestPrimer


TEST_F(TestPrimer, PredefinedTest)
{
  const Settings sets[] = {{1, 3, 'B'}};
  const Predictions expectations[] = {{-2, 'A'}, {-1, 'A'}, {0, 'A'}, {1, 'B'},
                                      {2, 'B'},  {3, 'A'},  {4, 'A'}, {5, 'A'}};
  setIntervals(sets, (int)(sizeof(sets) / sizeof(sets[0])));
  checkIntervals(expectations,
                 (int)(sizeof(expectations) / sizeof(expectations[0])));
}

TEST_F(TestPrimer, Simple)
{
  const Settings sets[] = {{1, 3, 'B'}};
  const Predictions expectations[] = {{0, 'A'}, {1, 'B'}, {2, 'B'}, {3, 'A'}};
  setIntervals(sets, (int)(sizeof(sets) / sizeof(sets[0])));
  checkIntervals(expectations,
                 (int)(sizeof(expectations) / sizeof(expectations[0])));
}

TEST_F(TestPrimer, DistinctSegments)
{
  const Settings sets[] = {{1, 3, 'B'}, {6, 8, 'C'}};
  const Predictions expectations[] = {{0, 'A'}, {1, 'B'}, {2, 'B'},
                                      {3, 'A'}, {4, 'A'}, {5, 'A'},
                                      {6, 'C'}, {7, 'C'}, {8, 'A'}};
  setIntervals(sets, (int)(sizeof(sets) / sizeof(sets[0])));
  checkIntervals(expectations,
                 (int)(sizeof(expectations) / sizeof(expectations[0])));
}

TEST_F(TestPrimer, PyramidUp)
{
  const Settings sets[] = {{1, 6, 'B'}, {3, 5, 'C'}};
  const Predictions expectations[] = {{0, 'A'}, {1, 'B'}, {2, 'B'}, {3, 'C'},
                                      {4, 'C'}, {5, 'B'}, {6, 'A'}};
  setIntervals(sets, (int)(sizeof(sets) / sizeof(sets[0])));
  checkIntervals(expectations,
                 (int)(sizeof(expectations) / sizeof(expectations[0])));
}

TEST_F(TestPrimer, PyramidDown)
{
  const Settings sets[] = {{3, 5, 'B'}, {1, 6, 'C'}};
  const Predictions expectations[] = {{0, 'A'}, {1, 'C'}, {2, 'C'}, {3, 'C'},
                                      {4, 'C'}, {5, 'C'}, {6, 'A'}};
  setIntervals(sets, (int)(sizeof(sets) / sizeof(sets[0])));
  checkIntervals(expectations,
                 (int)(sizeof(expectations) / sizeof(expectations[0])));
}

TEST_F(TestPrimer, GrowRight)
{
  const Settings sets[] = {{1, 5, 'B'}, {3, 6, 'B'}};
  const Predictions expectations[] = {{0, 'A'}, {1, 'B'}, {2, 'B'}, {3, 'B'},
                                      {4, 'B'}, {5, 'B'}, {6, 'A'}};
  setIntervals(sets, (int)(sizeof(sets) / sizeof(sets[0])));
  checkIntervals(expectations,
                 (int)(sizeof(expectations) / sizeof(expectations[0])));
}

TEST_F(TestPrimer, GrowLeftRight)
{
  const Settings sets[] = {{2, 3, 'B'}, {1, 5, 'B'}};
  const Predictions expectations[] = {{0, 'A'}, {1, 'B'}, {2, 'B'},
                                      {3, 'B'}, {4, 'B'}, {5, 'A'}};
  setIntervals(sets, (int)(sizeof(sets) / sizeof(sets[0])));
  checkIntervals(expectations,
                 (int)(sizeof(expectations) / sizeof(expectations[0])));
}

TEST_F(TestPrimer, OverrideLeft)
{
  const Settings sets[] = {{3, 6, 'C'}, {1, 5, 'B'}};
  const Predictions expectations[] = {{0, 'A'}, {1, 'B'}, {2, 'B'}, {3, 'B'},
                                      {4, 'B'}, {5, 'C'}, {6, 'A'}};
  setIntervals(sets, (int)(sizeof(sets) / sizeof(sets[0])));
  checkIntervals(expectations,
                 (int)(sizeof(expectations) / sizeof(expectations[0])));
}

TEST_F(TestPrimer, OverrideRightA)
{
  const Settings sets[] = {{1, 5, 'B'}, {3, 6, 'C'}};
  const Predictions expectations[] = {{0, 'A'}, {1, 'B'}, {2, 'B'}, {3, 'C'},
                                      {4, 'C'}, {5, 'C'}, {6, 'A'}};
  setIntervals(sets, (int)(sizeof(sets) / sizeof(sets[0])));
  checkIntervals(expectations,
                 (int)(sizeof(expectations) / sizeof(expectations[0])));
}

TEST_F(TestPrimer, GrowLeft)
{
  const Settings sets[] = {{3, 5, 'B'}, {1, 4, 'B'}};
  const Predictions expectations[] = {{0, 'A'}, {1, 'B'}, {2, 'B'},
                                      {3, 'B'}, {4, 'B'}, {5, 'A'}};
  setIntervals(sets, (int)(sizeof(sets) / sizeof(sets[0])));
  checkIntervals(expectations,
                 (int)(sizeof(expectations) / sizeof(expectations[0])));
}

TEST_F(TestPrimer, OverrideRightB)
{
  const Settings sets[] = {{2, 5, 'B'}, {5, 8, 'C'}, {4, 5, 'A'}};
  const Predictions expectations[] = {{0, 'A'}, {1, 'A'}, {2, 'B'},
                                      {3, 'B'}, {4, 'A'}, {5, 'C'},
                                      {6, 'C'}, {7, 'C'}, {8, 'A'}};
  setIntervals(sets, (int)(sizeof(sets) / sizeof(sets[0])));
  checkIntervals(expectations,
                 (int)(sizeof(expectations) / sizeof(expectations[0])));
}

TEST_F(TestPrimer, BetweenPriorLimits)
{
  const Settings sets[] = {{1, 5, 'B'}, {2, 3, 'B'}};
  const Predictions expectations[] = {{0, 'A'}, {1, 'B'}, {2, 'B'},
                                      {3, 'B'}, {4, 'B'}, {5, 'A'}};
  setIntervals(sets, (int)(sizeof(sets) / sizeof(sets[0])));
  checkIntervals(expectations,
                 (int)(sizeof(expectations) / sizeof(expectations[0])));
}

TEST_F(TestPrimer, ResetRight)
{
  const Settings sets[] = {{1, 5, 'B'}, {4, 6, 'A'}};
  const Predictions expectations[] = {{0, 'A'}, {1, 'B'}, {2, 'B'},
                                      {3, 'B'}, {4, 'A'}, {5, 'A'}};
  setIntervals(sets, (int)(sizeof(sets) / sizeof(sets[0])));
  checkIntervals(expectations,
                 (int)(sizeof(expectations) / sizeof(expectations[0])));
}

TEST_F(TestPrimer, SetResetSameInterval)
{
  const Settings sets[] = {{1, 5, 'B'}, {1, 5, 'A'}};
  const Predictions expectations[] = {{0, 'A'}, {1, 'A'}, {2, 'A'},
                                      {3, 'A'}, {4, 'A'}, {5, 'A'}};
  setIntervals(sets, (int)(sizeof(sets) / sizeof(sets[0])));
  checkIntervals(expectations,
                 (int)(sizeof(expectations) / sizeof(expectations[0])));
}

TEST_F(TestPrimer, DevelopmentTest0)
{
  const Settings sets[] = {
    {0, 6, 'a'}, {6, 10, 'b'}, {11, 17, 'c'}, {17, 25, 'b'}, {8, 20, 'v'}};
  const Predictions expectations[] = {{0, 'a'},  {6, 'b'},  {7, 'b'},
                                      {8, 'v'},  {19, 'v'}, {20, 'b'},
                                      {24, 'b'}, {25, 'A'}, {100, 'A'}};
  setIntervals(sets, (int)(sizeof(sets) / sizeof(sets[0])));
  checkIntervals(expectations,
                 (int)(sizeof(expectations) / sizeof(expectations[0])));
}

TEST_F(TestPrimer, DevelopmentTest1)
{
  const Settings sets[] = {{3, 6, 'B'}, {2, 5, 'C'}, {4, 7, 'A'}};
  const Predictions expectations[] = {{0, 'A'}, {1, 'A'}, {2, 'C'}, {3, 'C'},
                                      {4, 'A'}, {5, 'A'}, {6, 'A'}, {7, 'A'}};
  setIntervals(sets, (int)(sizeof(sets) / sizeof(sets[0])));
  checkIntervals(expectations,
                 (int)(sizeof(expectations) / sizeof(expectations[0])));
}

TEST_F(TestPrimer, DevelopmentTest2)
{
  const Settings sets[] = {
    {8, 12, 'B'}, {2, 12, 'B'}, {2, 12, 'C'}, {5, 12, 'C'},
    {4, 10, 'C'}, {4, 12, 'C'}, {8, 13, 'A'}, {6, 9, 'D'},
  };
  const Predictions expectations[] = {{0, 'A'}, {1, 'A'}, {2, 'C'}, {3, 'C'},
                                      {4, 'C'}, {5, 'C'}, {6, 'D'}, {7, 'D'},
                                      {8, 'D'}, {9, 'A'}};
  setIntervals(sets, (int)(sizeof(sets) / sizeof(sets[0])));
  checkIntervals(expectations,
                 (int)(sizeof(expectations) / sizeof(expectations[0])));
}

TEST_F(TestPrimer, RestoreInfinite)
{
  interval_map<unsigned int, char> map('A');

  struct
  {
    unsigned int L, R;
    char Label;
  } sets[] = {{1, 5, 'B'}, {0, 7, 'A'}};
  for (int i = 0; i < (int)(sizeof(sets) / sizeof(sets[0])); i++)
    map.assign(KeyType<unsigned int>(sets[i].L),
               KeyType<unsigned int>(sets[i].R), V(sets[i].Label));

  struct
  {
    unsigned int pos;
    char Label;
  } expectations[] = {{0, 'A'}, {1, 'A'}, {2, 'A'},
                      {3, 'A'}, {4, 'A'}, {5, 'A'}};
  for (int i = 0; i < (int)(sizeof(expectations) / sizeof(expectations[0]));
       i++)
    EXPECT_EQ(map[KeyType<unsigned int>(expectations[i].pos)].m_value,
              expectations[i].Label)
      << map;
}

TEST_F(TestPrimer, FloatKey)
{
  interval_map<float, char> map('A');

  struct
  {
    float L, R;
    char Label;
  } sets[] = {{-1, 1, 'B'}};
  for (int i = 0; i < (int)(sizeof(sets) / sizeof(sets[0])); i++)
    map.assign(KeyType<float>(sets[i].L), KeyType<float>(sets[i].R),
               V(sets[i].Label));

  struct
  {
    float pos;
    char Label;
  } expectations[] = {
    {-2.f, 'A'}, {-1.1f, 'A'}, {-1.f, 'B'}, {1.f, 'A'}, {1.1f, 'A'}};
  for (int i = 0; i < (int)(sizeof(expectations) / sizeof(expectations[0]));
       i++)
    EXPECT_EQ(map[KeyType<float>(expectations[i].pos)].m_value,
              expectations[i].Label)
      << map;
}

TEST_F(TestPrimer, StringKey)
{
  interval_map<std::string, char> map('A');

  struct
  {
    std::string L, R;
    char Label;
  } sets[] = {{"Alpha", "Beta", 'B'}, {"Delta", "Epsilon", 'C'}};
  for (int i = 0; i < (int)(sizeof(sets) / sizeof(sets[0])); i++)
    map.assign(KeyType<std::string>(sets[i].L), KeyType<std::string>(sets[i].R),
               V(sets[i].Label));

  struct
  {
    std::string pos;
    char Label;
  } expectations[] = {{"_LessThanAlpha", 'A'}, {"Alpha", 'B'},   {"Beta", 'A'},
                      {"Delta", 'C'},          {"Epsilon", 'A'}, {"Zeta", 'A'}};
  for (int i = 0; i < (int)(sizeof(expectations) / sizeof(expectations[0]));
       i++)
    EXPECT_EQ(map[KeyType<std::string>(expectations[i].pos)].m_value,
              expectations[i].Label)
      << map;
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}