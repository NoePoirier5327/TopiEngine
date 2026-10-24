#include <gtest/gtest.h>
#include "../src/topi/topi.hpp"

using namespace topi::type::vector;

TEST(Vector2f, isEqual) {
  Vector2f v = Vector2f(78.0f, -1.90f);
  Vector2f u = Vector2f(78.0f, -1.90f);

  EXPECT_TRUE(v == u);
}

TEST(Vector2f, isNotEqual) {
  Vector2f v = Vector2f(-66.0f, -1.78f);
  Vector2f u = Vector2f(-89.55f, 106.0f);

  EXPECT_TRUE(v != u);
}

TEST(Vector2f, sum) {
  Vector2f v = Vector2f(90.06f, 8.8f);
  Vector2f u = Vector2f(0.0f, -1.0f);
  Vector2f w = v + u;

  EXPECT_TRUE(w == Vector2f(90.06f, 7.8f));
}

TEST(Vector2f, sub) {
  Vector2f v = Vector2f(90.06f, 8.8f);
  Vector2f u = Vector2f(7.1f, -1.0f);
  Vector2f w = v - u;

  EXPECT_TRUE(w == Vector2f(82.96f, 9.8f));
}

TEST(Vector2f, rightIntProduct) {
  Vector2f v = Vector2f(-2.0f, -6.0f);
  Vector2f u = v * -2;

  EXPECT_TRUE(u == Vector2f(4.0f, 12.0f));
}

TEST(Vector2f, leftIntProduct) {
  Vector2f v = Vector2f(-2.0f, 6.0f);
  Vector2f u = -2 * v;

  EXPECT_TRUE(u == Vector2f(4.0f, -12.0f));
}

TEST(Vector2f, rightFloatProduct) {
  Vector2f v = Vector2f(2.0f, 6.0f);
  Vector2f u = v * 0.5f;

  EXPECT_TRUE(u == Vector2f(1.0f, 3.0f));
}

TEST(Vector2f, leftFloatProduct) {
  Vector2f v = Vector2f(3.0f, 9.0f);
  Vector2f u = 0.5f * v;

  EXPECT_TRUE(u == Vector2f(1.5f, 4.5f));
}

TEST(Vector2f, rightDoubleProduct) {
  Vector2f v = Vector2f(2.0f, -9.0f);
  Vector2f u = v * 1.5;

  EXPECT_TRUE(u == Vector2f(3.0f, -13.5f));
}

TEST(Vector2f, leftDoubleProduct) {
  Vector2f v = Vector2f(3.0f, -9.0f);
  Vector2f u = 1.5 * v;

  EXPECT_TRUE(u == Vector2f(4.5f, -13.5f));
}

