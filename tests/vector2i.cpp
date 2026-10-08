#include <gtest/gtest.h>
#include "../src/topi/topi.hpp"

using namespace topi::toolkit::vector;

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

TEST(Vector2i, product) {
  Vector2i v = Vector2i(-2, -6);
  Vector2i u = v * -2;

  EXPECT_TRUE(u == Vector2i(4, 12));
}
