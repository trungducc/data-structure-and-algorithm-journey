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

TEST(SortingTest, SelectionSort) {
  std::vector<int> items({2, 8, 4, 7, 5, 9, 1, 3, 6});
  selection_sort(items);
  EXPECT_EQ(std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}), items);

  items = std::vector<int>({2, 8, 4, 7, 5, 9, 1, 3, 6});
  selection_sort(items, false);
  EXPECT_EQ(std::vector<int>({9, 8, 7, 6, 5, 4, 3, 2, 1}), items);

  items = std::vector<int>();
  selection_sort(items);
  EXPECT_EQ(std::vector<int>(), items);
}

TEST(SortingTest, InsertionSort) {
  std::vector<int> items({2, 8, 4, 7, 5, 9, 1, 3, 6});
  insertion_sort(items);
  EXPECT_EQ(std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}), items);

  items = std::vector<int>({2, 8, 4, 7, 5, 9, 1, 3, 6});
  insertion_sort(items, false);
  EXPECT_EQ(std::vector<int>({9, 8, 7, 6, 5, 4, 3, 2, 1}), items);

  items = std::vector<int>();
  insertion_sort(items);
  EXPECT_EQ(std::vector<int>(), items);
}

TEST(SortingTest, HeapSort) {
  std::vector<int> items({2, 8, 4, 7, 5, 9, 1, 3, 6});
  heap_sort(items);
  EXPECT_EQ(std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}), items);

  items = std::vector<int>({2, 8, 4, 7, 5, 9, 1, 3, 6});
  heap_sort(items, false);
  EXPECT_EQ(std::vector<int>({9, 8, 7, 6, 5, 4, 3, 2, 1}), items);

  items = std::vector<int>();
  heap_sort(items);
  EXPECT_EQ(std::vector<int>(), items);
}

TEST(SortingTest, MergeSort) {
  std::vector<int> items({2, 8, 4, 7, 5, 9, 1, 3, 6});
  merge_sort(items);
  EXPECT_EQ(std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}), items);

  items = std::vector<int>({2, 8, 4, 7, 5, 9, 1, 3, 6});
  merge_sort(items, false);
  EXPECT_EQ(std::vector<int>({9, 8, 7, 6, 5, 4, 3, 2, 1}), items);

  items = std::vector<int>();
  merge_sort(items);
  EXPECT_EQ(std::vector<int>(), items);
}

TEST(SortingTest, QuickSort) {
  std::vector<int> items({2, 8, 4, 7, 5, 9, 1, 3, 6});
  quick_sort(items);
  EXPECT_EQ(std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}), items);

  items = std::vector<int>({2, 8, 4, 7, 5, 9, 1, 3, 6});
  quick_sort(items, false);
  EXPECT_EQ(std::vector<int>({9, 8, 7, 6, 5, 4, 3, 2, 1}), items);

  items = std::vector<int>();
  quick_sort(items);
  EXPECT_EQ(std::vector<int>(), items);
}

}  // namespace
