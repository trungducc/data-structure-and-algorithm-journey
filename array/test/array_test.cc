#include "array/array.h"
#include "gtest/gtest.h"

namespace {

using namespace td;

TEST(ArrayTest, DefaultConstructor) {
  Array<int> array;
  EXPECT_EQ(0, array.size());
  EXPECT_EQ(16, array.capacity());
}

TEST(ArrayTest, CapacityConstructor) {
  Array<int> array(30);
  EXPECT_EQ(0, array.size());
  EXPECT_EQ(30, array.capacity());
}

TEST(ArrayTest, InitializerListConstructor) {
  Array<int> array({0, 1, 2, 3, 4, 5});
  EXPECT_EQ(6, array.size());
  EXPECT_EQ(16, array.capacity());

  array =
      Array<int>({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
  EXPECT_EQ(17, array.size());
  EXPECT_EQ(32, array.capacity());
}

TEST(ArrayTest, BracketOperator) {
  Array<int> array({0, 1, 2, 3, 4, 5});
  EXPECT_EQ(0, array[0]);
  EXPECT_EQ(5, array[5]);

  array[2] = 10;
  EXPECT_EQ(10, array[2]);
}

TEST(ArrayTest, Size) {
  Array<int> array({0, 1, 2});
  EXPECT_EQ(3, array.size());

  array = Array<int>();
  EXPECT_EQ(0, array.size());
}

TEST(ArrayTest, Capacity) {
  Array<int> array({0, 1, 2});
  EXPECT_EQ(16, array.capacity());

  array = Array<int>();
  EXPECT_EQ(16, array.capacity());
}

TEST(ArrayTest, IsEmpty) {
  Array<int> array({0, 1, 2});
  EXPECT_FALSE(array.is_empty());

  array = Array<int>();
  EXPECT_TRUE(array.is_empty());
}

TEST(ArrayTest, ItemAt) {
  Array<int> array;
  EXPECT_THROW(array.item_at(0), std::out_of_range);
  EXPECT_THROW(array.item_at(2), std::out_of_range);

  array = Array<int>({0, 1, 2});
  EXPECT_EQ(0, array.item_at(0));
  EXPECT_EQ(1, array.item_at(1));
  EXPECT_EQ(2, array.item_at(2));
}

TEST(ArrayTest, Append) {
  Array<int> array =
      Array<int>({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15});
  array.append(16);

  EXPECT_EQ(16, array.item_at(16));
  EXPECT_EQ(17, array.size());
  EXPECT_EQ(32, array.capacity());
}

TEST(ArrayTest, Insert) {
  Array<int> array;
  array.insert(1, 0);
  EXPECT_EQ(1, array.item_at(0));

  array = Array<int>({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13});
  EXPECT_THROW(array.insert(0, 16), std::out_of_range);

  array.insert(14, 14);
  EXPECT_EQ(14, array.item_at(14));

  array.insert(0, 0);

  EXPECT_EQ(0, array.item_at(0));
  EXPECT_EQ(16, array.size());
  EXPECT_EQ(16, array.capacity());

  array.insert(0, 15);

  EXPECT_EQ(0, array.item_at(15));
  EXPECT_EQ(14, array.item_at(16));
  EXPECT_EQ(17, array.size());
  EXPECT_EQ(32, array.capacity());
}

TEST(ArrayTest, Prepend) {
  Array<int> array;

  array.prepend(0);
  EXPECT_EQ(0, array.item_at(0));

  array.prepend(-1);
  EXPECT_EQ(-1, array.item_at(0));
  EXPECT_EQ(0, array.item_at(1));
}

TEST(ArrayTest, Pop) {
  Array<int> array;
  EXPECT_THROW(array.pop(), std::out_of_range);

  array =
      Array<int>({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
  EXPECT_EQ(16, array.pop());
  EXPECT_EQ(16, array.size());
  EXPECT_EQ(32, array.capacity());
  EXPECT_EQ(15, array.item_at(15));

  array.pop();
  array.pop();
  array.pop();
  array.pop();
  array.pop();
  array.pop();
  array.pop();
  EXPECT_EQ(32, array.capacity());
  array.pop();
  EXPECT_EQ(16, array.capacity());
}

TEST(ArrayTest, RemoveAt) {
  Array<int> array({0, 1, 2});
  EXPECT_THROW(array.remove_at(3), std::out_of_range);

  array.remove_at(0);
  EXPECT_EQ(1, array.item_at(0));
  EXPECT_EQ(2, array.item_at(1));

  array.remove_at(1);
  EXPECT_EQ(1, array.item_at(0));

  array.remove_at(0);
  EXPECT_TRUE(array.is_empty());
}

TEST(ArrayTest, Remove) {
  Array<int> array({0, 1, 2});

  array.remove(-1);
  EXPECT_EQ(3, array.size());
  EXPECT_EQ(0, array.item_at(0));
  EXPECT_EQ(1, array.item_at(1));
  EXPECT_EQ(2, array.item_at(2));

  array.remove(1);
  EXPECT_EQ(2, array.size());
  EXPECT_EQ(0, array.item_at(0));
  EXPECT_EQ(2, array.item_at(1));
}

TEST(ArrayTest, Find) {
  Array<int> array({0, 1, 2});

  EXPECT_EQ(index_not_found, array.find(-1));
  EXPECT_EQ(0, array.find(0));
  EXPECT_EQ(1, array.find(1));
  EXPECT_EQ(2, array.find(2));
}
}

