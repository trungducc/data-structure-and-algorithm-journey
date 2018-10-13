#include "utils/utils.h"
#include "gtest/gtest.h"

namespace {

using namespace td::utils;

TEST(UtilsTest, Validate) {
  validate(1, 2, Action::kNone);
  EXPECT_THROW(validate(2, 2, Action::kNone), std::out_of_range);

  validate(10, 11, Action::kRemoved);
  EXPECT_THROW(validate(0, 0, Action::kRemoved), std::out_of_range);
  EXPECT_THROW(validate(1, 0, Action::kRemoved), std::out_of_range);

  validate(0, 0, Action::kInserted);
  validate(10, 10, Action::kInserted);
  EXPECT_THROW(validate(1, 0, Action::kInserted), std::out_of_range);
}

TEST(UtilsTest, IsPrime) {
  EXPECT_FALSE(is_prime(1));
  EXPECT_TRUE(is_prime(2));
  EXPECT_TRUE(is_prime(3));
  EXPECT_FALSE(is_prime(4));
  EXPECT_TRUE(is_prime(5));
  EXPECT_FALSE(is_prime(6));
  EXPECT_TRUE(is_prime(7));
  EXPECT_FALSE(is_prime(8));
  EXPECT_FALSE(is_prime(9));
  EXPECT_FALSE(is_prime(10));
  EXPECT_TRUE(is_prime(11));
  EXPECT_FALSE(is_prime(12));
  EXPECT_TRUE(is_prime(13));
  EXPECT_FALSE(is_prime(14));
  EXPECT_FALSE(is_prime(15));
  EXPECT_FALSE(is_prime(16));
  EXPECT_TRUE(is_prime(17));
  EXPECT_FALSE(is_prime(18));
  EXPECT_TRUE(is_prime(19));
  EXPECT_FALSE(is_prime(20));
  EXPECT_FALSE(is_prime(21));
  EXPECT_FALSE(is_prime(22));
  EXPECT_TRUE(is_prime(23));
  EXPECT_FALSE(is_prime(24));
  EXPECT_FALSE(is_prime(25));
  EXPECT_FALSE(is_prime(26));
  EXPECT_FALSE(is_prime(27));
  EXPECT_FALSE(is_prime(28));
  EXPECT_TRUE(is_prime(29));
  EXPECT_FALSE(is_prime(30));
}

TEST(UtilsTest, NextPrime) {
  EXPECT_EQ(2, next_prime(1));
  EXPECT_EQ(2, next_prime(2));
  EXPECT_EQ(3, next_prime(3));
  EXPECT_EQ(23, next_prime(20));
  EXPECT_EQ(29, next_prime(25));
  EXPECT_EQ(59, next_prime(56));
  EXPECT_EQ(127, next_prime(115));
}

}  // namespace