#include "sorting/sorting.h"
#include "gtest/gtest.h"

namespace {
using namespace td::sorting;

TEST(SortingTest, BubleSort) {
  std::vector<int> items({2, 8, 4, 7, 5, 9, 1, 3, 6});
  bubble_sort(items);
  EXPECT_EQ(std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}), items);

  items = std::vector<int>({2, 8, 4, 7, 5, 9, 1, 3, 6});
  bubble_sort(items, false);
  EXPECT_EQ(std::vector<int>({9, 8, 7, 6, 5, 4, 3, 2, 1}), items);

  items = std::vector<int>();
  bubble_sort(items);
  EXPECT_EQ(std::vector<int>(), items);
}

}  // namespace
