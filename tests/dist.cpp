#include <gtest/gtest.h>
#include "../src/topi/topi.hpp"

TEST(dist, intPoints) {
  EXPECT_EQ(topi::toolkit::dist(1, 2, 2, 2), 1.0);
}

TEST(dist, floatPoints) {
  EXPECT_EQ(topi::toolkit::dist(4.0f, 0.0f, 2.0f, 0.0f), 2.0);
}

TEST(dist, doublePoints) {
  EXPECT_EQ(topi::toolkit::dist(1.0, 1.0, 2.0, 1.0), 1.0);
}
