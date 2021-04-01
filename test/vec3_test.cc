#include "vec3.h"

#include "gtest/gtest.h"

using namespace radacuda;

TEST(Vec3Test, AdditionWorks) {
  vec3 a(1, 2, 3);
  vec3 b(3, 2, 1);
  EXPECT_EQ(a + b, vec3(4, 4, 4));
  a += b;
  EXPECT_EQ(a, vec3(4, 4, 4));
}

TEST(Vec3Test, SubtractionWorks) {
  vec3 a(1, 2, 3);
  vec3 b(3, 2, 1);
  EXPECT_EQ(a - b, vec3(-2, 0, 2));
  a -= b;
  EXPECT_EQ(a, vec3(-2, 0, 2));
}

TEST(Vec3Test, MultiplicationWorks) {
  vec3 a(1, 2, 3);
  vec3 b(3, 2, 5);
  EXPECT_EQ(a * b, vec3(3, 4, 15));
  a *= b;
  EXPECT_EQ(a, vec3(3, 4, 15));
}

TEST(Vec3Test, ScalarMultiplicationWorks) {
  vec3 a(1, 2, 3);
  double x = 5;
  EXPECT_EQ(a * x, vec3(5, 10, 15));
  EXPECT_EQ(x * a, vec3(5, 10, 15));
  a *= x;
  EXPECT_EQ(a, vec3(5, 10, 15));
}

TEST(Vec3Test, ScalarDivisionWorks) {
  vec3 a(5, 10, 15);
  double x = 5;
  EXPECT_EQ(a / x, vec3(1, 2, 3));
  a /= x;
  EXPECT_EQ(a, vec3(1, 2, 3));
}