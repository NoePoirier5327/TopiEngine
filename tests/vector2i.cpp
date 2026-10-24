#include <gtest/gtest.h>
#include "../src/topi/topi.hpp"

using namespace topi::type::vector;

TEST(Vector2i, isEqual) {
  Vector2i v = Vector2i(9, -1);
  Vector2i u = Vector2i(9, -1);

  EXPECT_TRUE(v == u);
}

TEST(Vector2i, isNotEqual) {
  Vector2i v = Vector2i(6, -1);
  Vector2i u = Vector2i(-89, 106);

  EXPECT_FALSE(v == u);
}

TEST(Vector2i, sum) {
  Vector2i v = Vector2i(90, 8);
  Vector2i u = Vector2i(0, -1);
  Vector2i w = v + u;

  EXPECT_TRUE(w == Vector2i(90, 7));
}

TEST(Vector2i, rightIntProduct) {
  Vector2i v = Vector2i(-2, -6);
  Vector2i u = v * -2;

  EXPECT_TRUE(u == Vector2i(4, 12));
}

TEST(Vector2i, leftIntProduct) {
  Vector2i v = Vector2i(-2, 6);
  Vector2i u = -2 * v;

  EXPECT_TRUE(u == Vector2i(4, -12));
}

TEST(Vector2i, rightFloatProduct) {
  Vector2i v = Vector2i(2, 6);
  Vector2i u = v * 0.5f;

  EXPECT_TRUE(u == Vector2i(1, 3));
}

TEST(Vector2i, leftFloatProduct) {
  Vector2i v = Vector2i(3, 9);
  Vector2i u = 0.5f * v;

  EXPECT_TRUE(u == Vector2i(1, 4));
}

TEST(Vector2i, rightDoubleProduct) {
  Vector2i v = Vector2i(2, -6);
  Vector2i u = v * 1.5f;

  EXPECT_TRUE(u == Vector2i(3, -9));
}

TEST(Vector2i, leftDoubleProduct) {
  Vector2i v = Vector2i(3, -9);
  Vector2i u = 1.5f * v;

  EXPECT_TRUE(u == Vector2i(4, -13));
}
