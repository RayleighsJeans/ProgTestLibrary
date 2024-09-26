#include <gtest/gtest.h>

#include "../include/shuntingYard.hpp"


using namespace shunting_yard;


TEST(ManualShuntingYardTests, SimpleTestA)
{
  const char expression[] = "";
  int result;
  EXPECT_FALSE(compute(expression, result));
}

TEST(ManualShuntingYardTests, SimpleTestB)
{
  const char expression[] = "1";
  int result;
  EXPECT_TRUE(compute(expression, result));
  EXPECT_EQ(result, 1);
}

TEST(ManualShuntingYardTests, SimpleTestC)
{
  const char expression[] = "1 +";
  int result;
  EXPECT_FALSE(compute(expression, result));
}

TEST(ManualShuntingYardTests, SimpleTestD)
{
  const char expression[] = "+ 1";
  int result;
  EXPECT_FALSE(compute(expression, result));
}

TEST(ManualShuntingYardTests, SimpleTestE)
{
  const char expression[] = "1 + 3";
  int result;
  EXPECT_TRUE(compute(expression, result));
  EXPECT_EQ(result, 4);
}

TEST(ManualShuntingYardTests, SimpleTestF)
{
  const char expression[] = "1 + -2 + 3";
  int result;
  EXPECT_TRUE(compute(expression, result));
  EXPECT_EQ(result, 2);
}

TEST(ManualShuntingYardTests, SimpleTestG)
{
  const char expression[] = "-1 + 23 + 456 + 789 + 9000";
  int result;
  EXPECT_TRUE(compute(expression, result));
  EXPECT_EQ(result, 10267);
}

TEST(ManualShuntingYardTests, SimpleTestH)
{
  const char expression[] = "(1 + 3) * 2";
  int result;
  EXPECT_TRUE(compute(expression, result));
  EXPECT_EQ(result, 8);
}

TEST(ManualShuntingYardTests, SimpleTestI)
{
  const char expression[] = "(4 / 2) + 6";
  int result;
  EXPECT_TRUE(compute(expression, result));
  EXPECT_EQ(result, 8);
}

TEST(ManualShuntingYardTests, SimpleTestJ)
{
  const char expression[] = "4 + (12 / (1 * 2))";
  int result;
  EXPECT_TRUE(compute(expression, result));
  EXPECT_EQ(result, 10);
}

TEST(ManualShuntingYardTests, SimpleTestK)
{
  const char expression[] = "(1 + (12 * 2)";
  int result;
  EXPECT_FALSE(compute(expression, result));
}

TEST(ManualShuntingYardTests, SimpleTestL)
{
  const char expression[] = "()";
  int result;
  EXPECT_FALSE(compute(expression, result));
}

TEST(ManualShuntingYardTests, SimpleTestM)
{
  const char expression[] = "1 - 6)";
  int result;
  EXPECT_FALSE(compute(expression, result));
}

TEST(ManualShuntingYardTests, SimpleTestN)
{
  const char expression[] = "(()";
  int result;
  EXPECT_FALSE(compute(expression, result));
}

TEST(ManualShuntingYardTests, SimpleTestO)
{
  const char expression[] = "1 + 3 * 2 )";
  int result;
  EXPECT_FALSE(compute(expression, result));
}

TEST(ManualShuntingYardTests, SimpleTestP)
{
  const char expression[] = "0 = a * x^2 + b * x + c";
  int result;
  EXPECT_FALSE(compute(expression, result));
}

TEST(ManualShuntingYardTests, SimpleTestQ)
{
  const char expression[] = "foo";
  int result;
  EXPECT_FALSE(compute(expression, result));
}

TEST(ManualShuntingYardTests, SimpleTestR)
{
  const char expression[] = "4 * (12 + 3 - 7 * 3 * ())";
  int result;
  EXPECT_FALSE(compute(expression, result));
}

TEST(ManualShuntingYardTests, SimpleTestS)
{
  const char expression[] = "4 + * / 1 2 3";
  int result;
  EXPECT_FALSE(compute(expression, result));
}

TEST(ManualShuntingYardTests, SimpleTestT)
{
  const char expression[] = "-4 / 10 * 10 + -8";
  int result;
  EXPECT_TRUE(compute(expression, result));
  EXPECT_EQ(result, -12);
}

TEST(ManualShuntingYardTests, SimpleTestU)
{
  const char expression[] = "3 - -1 + -5 / 5";
  int result;
  EXPECT_TRUE(compute(expression, result));
  EXPECT_EQ(result, 3);
}

#ifdef __linux__
TEST(ManualShuntingYardTests, SimpleTestV)
{
  const char expression[] = "2147483647 + 2147483647";
  int result;
  EXPECT_TRUE(compute(expression, result));
  EXPECT_EQ(result, -2147483648);
}
#else
TEST(ManualShuntingYardTests, SimpleTestV)
{
  const char expression[] = "2147483647 + 2147483647";
  int result;
  EXPECT_TRUE(compute(expression, result));
  EXPECT_EQ(result, 2147483647);
}
#endif

TEST(ManualShuntingYardTests, SimpleTestW)
{
  std::vector<std::string> expressions = {
    "-7648*3115*()--83237153", "-9783(1617-1376(((*(",
    "1954-3927-)()(22247011",  "7474)-6763/(-3753(/(",
    "-81988002--8099))8369)",  "-93262106((655890333",
    "-12892764/-959)(()",      "3740)5864(--2908(-43183113"};
  int result;
  for (auto& exp : expressions)
    EXPECT_FALSE(compute(exp.c_str(), result));
}

TEST(ManualShuntingYardTests, SimpleTestX)
{
  std::string expression = "1 / 0";
  int result;
  EXPECT_FALSE(compute(expression.c_str(), result));
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}