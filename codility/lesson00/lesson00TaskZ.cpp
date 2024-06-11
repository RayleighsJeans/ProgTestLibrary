#include "../../include/header.hpp"


using namespace helper;


int main()
{
  WriteToFile<int> file(__FILE__);
  RandomGenerator<int> gen(-10, 10);

  auto vector = gen.randomVector(10);
  print<char[], int>("vector A", vector);
  file(vector);
  auto vectorMax = std::max_element(vector.begin(), vector.end());
  file(*vectorMax);
  file.flush();

  vector = gen.randomVector(1, 20);
  print<char[], int>("vector", vector);
  file(vector);
  vectorMax = std::max_element(vector.begin(), vector.end());
  file(*vectorMax);
  file.flush();

  auto vector2d = gen.random2dVector(5, 3);
  print<char[], int>("vector 2D A", vector2d);
  file(vector2d);
  auto vector2dMax = helper::max_element<int>(vector2d);
  file(*vector2dMax);
  file.flush();

  vector2d = gen.random2dVector(1, 10, 1, 10);
  print<char[], int>("vector 2D", vector2d);
  file(vector2d);
  vector2dMax = helper::max_element<int>(vector2d);
  file(*vector2dMax);
  file.flush();
} // main