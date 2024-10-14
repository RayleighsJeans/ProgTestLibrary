#include <gtest/gtest.h>

#include "../../../include/header.hpp"
#include "../include/interval_map.hpp"


using TypeK = int;
using TypeV = int;

using namespace think_cell;

using K = KeyType<TypeK>;
using V = ValueType<TypeV>;


// #define DEBUG


class TestPrimer : public ::testing::Test
{
 public:
  interval_map<K, V> m_intervalMap;

 protected:
  TestPrimer() : m_intervalMap(interval_map<K, V>(V(0))){};
  ~TestPrimer() = default;

  void message(const int atp, const TypeK L, const TypeK R, const TypeV M,
               const TypeV mapValue) const
  {
    const auto diff = fabs(R - L);
    std::cout << atp << " [" << L << ", " << R << "] " << diff << " " << M
              << " (" << mapValue << ")"
              << "\n";
  }

  void print() { m_intervalMap.print(); }

  bool validate() { return m_intervalMap.validate(); }

  void assign(const TypeK L, const TypeK R, const TypeV M)
  {
    m_intervalMap.assign(K(L), K(R), V(M));
  }

  void assignTest(const TypeK L, const TypeK R, const TypeV M)
  {
    m_intervalMap.assignTest(K(L), K(R), V(M));
  }

  V get(const K it) const { return m_intervalMap[it].m_value; }
}; // class TestPrimer


#ifndef DEBUG
constexpr int ScaleFactor = 6000;
#else
constexpr int ScaleFactor = 1;
#endif

int Counter = 0;

TEST_F(TestPrimer, AddRight)
{
  const int width = 10;
  const int MaxTest = 1000 * ScaleFactor;
  const int ExpectedSize = MaxTest + 1;

  helper::Timer t;
  int v = 0;

  t.tick();
  for (int i = 0; i < MaxTest; i++)
    assign(i * width, (i + 1) * width, v--);
  t.tock();

  EXPECT_LE(t.elapsed(), 4000);
  EXPECT_EQ(m_intervalMap.map().size(), ExpectedSize) << m_intervalMap;

  Counter = v;
}

TEST_F(TestPrimer, Pyramid)
{
  const int MaxTest = ScaleFactor * 10;
  const int ExpectedSize = MaxTest;

  helper::Timer t;
  int v = Counter;

  t.tick();
  for (int i = 0; i < MaxTest; i++) {
    v = Counter - 1;
    assign(i, MaxTest - i, v);
    Counter--;
  }
  t.tock();

  EXPECT_LE(t.elapsed(), 20);
  EXPECT_EQ(m_intervalMap.map().size(), ExpectedSize) << m_intervalMap;

  Counter = v;
}

TEST_F(TestPrimer, Skew)
{
  const int Scale = (int)sqrt(ScaleFactor);
  const int MaxTests = 100 * Scale;
  const int MaxDrift = 100 * Scale;
  const int ExpectedSize = MaxTests + MaxDrift - 1;

  helper::Timer t;
  int v = Counter;

  t.tick();
  for (int k = 0; k < MaxDrift; k++)
    for (int i = 0; i < MaxTests; i++)
      assign(k + i, k + MaxTests - i, v--);
  t.tock();

  EXPECT_LE(t.elapsed(), 8000);
  EXPECT_EQ(m_intervalMap.map().size(), ExpectedSize) << m_intervalMap;

  Counter = v;
}

TEST_F(TestPrimer, Remove)
{
  const int Scale = (int)sqrt(ScaleFactor);
  const int width = 1;
  const int stride = 10;
  const int MaxDrift = 100 * Scale;
  const int MaxTests = 100 * Scale;
  const int ExpectedSize = 3;

  helper::Timer t;
  int v = Counter;

  t.tick();
  for (int k = 0; k < MaxDrift; k++) {
    for (int i = 0; i < MaxTests; i++) {
      assign(k * i * width, k * (i + 1) * width, v--);
    }
    int to = k * (MaxTests + 1) * width;
    for (int i = MaxTests; i > 0; i -= stride) {
      assign(i, to, v--);
    }
  }
  t.tock();

  EXPECT_LE(t.elapsed(), 9000);
  EXPECT_EQ(m_intervalMap.map().size(), ExpectedSize) << m_intervalMap;
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
