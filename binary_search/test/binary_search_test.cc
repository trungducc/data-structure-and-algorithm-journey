#include "binary_search/binary_search.h"
#include "gtest/gtest.h"

namespace {
using namespace td;

TEST(BinarySearchTest, BinarySearch) {
  std::vector<int> vector({2, 3, 5, 7, 9, 13, 17, 19, 22, 34, 37, 56, 87, 88, 92, 93, 100});

  EXPECT_EQ(0, binary_search(vector, 2));
  EXPECT_EQ(1, binary_search(vector, 3));
  EXPECT_EQ(2, binary_search(vector, 5));
  EXPECT_EQ(3, binary_search(vector, 7));
  EXPECT_EQ(4, binary_search(vector, 9));
  EXPECT_EQ(5, binary_search(vector, 13));
  EXPECT_EQ(6, binary_search(vector, 17));
  EXPECT_EQ(7, binary_search(vector, 19));
  EXPECT_EQ(8, binary_search(vector, 22));
  EXPECT_EQ(9, binary_search(vector, 34));
  EXPECT_EQ(10, binary_search(vector, 37));
  EXPECT_EQ(11, binary_search(vector, 56));
  EXPECT_EQ(12, binary_search(vector, 87));
  EXPECT_EQ(13, binary_search(vector, 88));
  EXPECT_EQ(14, binary_search(vector, 92));
  EXPECT_EQ(15, binary_search(vector, 93));
  EXPECT_EQ(16, binary_search(vector, 100));

  EXPECT_EQ(-1, binary_search(vector, 1));
  EXPECT_EQ(-1, binary_search(vector, 23));
  EXPECT_EQ(-1, binary_search(vector, 86));
  EXPECT_EQ(-1, binary_search(vector, 89));
}

TEST(BinarySearchTest, RecursionBinarySearch) {
  std::vector<int> vector({2, 3, 5, 7, 9, 13, 17, 19, 22, 34, 37, 56, 87, 88, 92, 93, 100});

  EXPECT_EQ(0, recursion_binary_search(vector, 2, 0, 16));
  EXPECT_EQ(1, recursion_binary_search(vector, 3, 0, 16));
  EXPECT_EQ(2, recursion_binary_search(vector, 5, 0, 16));
  EXPECT_EQ(3, recursion_binary_search(vector, 7, 0, 16));
  EXPECT_EQ(4, recursion_binary_search(vector, 9, 0, 16));
  EXPECT_EQ(5, recursion_binary_search(vector, 13, 0, 16));
  EXPECT_EQ(6, recursion_binary_search(vector, 17, 0, 16));
  EXPECT_EQ(7, recursion_binary_search(vector, 19, 0, 16));
  EXPECT_EQ(8, recursion_binary_search(vector, 22, 0, 16));
  EXPECT_EQ(9, recursion_binary_search(vector, 34, 0, 16));
  EXPECT_EQ(10, recursion_binary_search(vector, 37, 0, 16));
  EXPECT_EQ(11, recursion_binary_search(vector, 56, 0, 16));
  EXPECT_EQ(12, recursion_binary_search(vector, 87, 0, 16));
  EXPECT_EQ(13, recursion_binary_search(vector, 88, 0, 16));
  EXPECT_EQ(14, recursion_binary_search(vector, 92, 0, 16));
  EXPECT_EQ(15, recursion_binary_search(vector, 93, 0, 16));
  EXPECT_EQ(16, recursion_binary_search(vector, 100, 0, 16));

  EXPECT_EQ(-1, recursion_binary_search(vector, 1, 0, 16));
  EXPECT_EQ(-1, recursion_binary_search(vector, 23, 0, 16));
  EXPECT_EQ(-1, recursion_binary_search(vector, 86, 0, 16));
  EXPECT_EQ(-1, recursion_binary_search(vector, 89, 0, 16));
}

}  // namespace

