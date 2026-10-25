#include <gtest/gtest.h>
#include "../src/topi/topi.hpp"

using namespace topi::type::vector;

TEST(Vector2d, isEqual) {
  Vector2d v = Vector2d(78.0, -1.90);
  Vector2d u = Vector2d(78.0, -1.90);

  EXPECT_TRUE(v == u);
}

TEST(Vector2d, isNotEqual) {
  Vector2d v = Vector2d(-66.0, -1.78);
  Vector2d u = Vector2d(-89.55, 106.0);

  EXPECT_TRUE(v != u);
}

TEST(Vector2d, sum) {
  Vector2d v = Vector2d(90.06, 8.8);
  Vector2d u = Vector2d(0.0, 2.0);
  Vector2d w = v + u;

  EXPECT_TRUE(w == Vector2d(90.06, 10.8));
}

TEST(Vector2d, sub) {
  Vector2d v = Vector2d(90.06, 8.8);
  Vector2d u = Vector2d(7.0, -2.0);
  Vector2d w = v - u;

  EXPECT_TRUE(w == Vector2d(83.06, 10.8));
}

TEST(Vector2d, sumThenAssign) {
  Vector2d v = Vector2d(90.06, 8.8);
  v += Vector2d(0.0, 2.0); 
  EXPECT_TRUE(v == Vector2d(90.06, 10.8));
}

TEST(Vector2d, subThenAssign) {
  Vector2d v = Vector2d(90.06, 8.8);
  v -= Vector2d(1.2, -1.2);
  EXPECT_TRUE(v == Vector2d(88.86, 10.0));
}

TEST(Vector2d, rightIntProduct) {
  Vector2d v = Vector2d(-2.0, -6.0);
  Vector2d u = v * -2;

  EXPECT_TRUE(u == Vector2d(4.0, 12.0));
}

TEST(Vector2d, leftIntProduct) {
  Vector2d v = Vector2d(-2.0, 6.0);
  Vector2d u = -2 * v;

  EXPECT_TRUE(u == Vector2d(4.0, -12.0));
}

TEST(Vector2d, rightFloatProduct) {
  Vector2d v = Vector2d(2.0, 6.0);
  Vector2d u = v * 0.5f;

  EXPECT_TRUE(u == Vector2d(1.0, 3.0));
}

TEST(Vector2d, leftFloatProduct) {
  Vector2d v = Vector2d(3.0, 9.0);
  Vector2d u = 0.5f * v;

  EXPECT_TRUE(u == Vector2d(1.5, 4.5));
}

TEST(Vector2d, rightDoubleProduct) {
  Vector2d v = Vector2d(2.0, -9.0);
  Vector2d u = v * 1.5;

  EXPECT_TRUE(u == Vector2d(3.0, -13.5));
}

TEST(Vector2d, leftDoubleProduct) {
  Vector2d v = Vector2d(3.0, -9.0);
  Vector2d u = 1.5 * v;

  EXPECT_TRUE(u == Vector2d(4.5, -13.5));
}

TEST(Vector2d, intProductThenAssign) {
  Vector2d v = Vector2d(3.0, -1.0);
  v *= 7;
  EXPECT_TRUE(v == Vector2d(21.0, -7.0));
}

TEST(Vector2d, floatProductThenAssign) {
  Vector2d v = Vector2d(5.0, -7.0);
  v *= -0.5f;
  EXPECT_TRUE(v == Vector2d(-2.5, 3.5));
}

TEST(Vector2d, doubleProductThenAssign) {
  Vector2d v = Vector2d(-5.0, -7.0);
  v *= 1.5;
  EXPECT_TRUE(v == Vector2d(-7.5, -10.5));
}

