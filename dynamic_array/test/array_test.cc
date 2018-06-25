#include "array.h"

#include "gtest/gtest.h"

namespace {

using namespace td;

TEST(ArrayTest, DefaultConstructor) {
  Array<int> array;
  EXPECT_EQ(0, array.GetSize());
  EXPECT_EQ(16, array.GetCapacity());
}

TEST(ArrayTest, CapacityConstructor) {
  Array<int> array(30);
  EXPECT_EQ(0, array.GetSize());
  EXPECT_EQ(30, array.GetCapacity());
}

TEST(ArrayTest, InitializerListConstructor) {
  Array<int> array({0, 1, 2, 3, 4, 5});
  EXPECT_EQ(6, array.GetSize());
  EXPECT_EQ(16, array.GetCapacity());

  array =
      Array<int>({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
  EXPECT_EQ(17, array.GetSize());
  EXPECT_EQ(32, array.GetCapacity());
}

TEST(ArrayTest, GetSize) {
  Array<int> array({0, 1, 2});
  EXPECT_EQ(3, array.GetSize());

  array = Array<int>();
  EXPECT_EQ(0, array.GetSize());
}

TEST(ArrayTest, GetCapacity) {
  Array<int> array({0, 1, 2});
  EXPECT_EQ(16, array.GetCapacity());

  array = Array<int>();
  EXPECT_EQ(16, array.GetCapacity());
}

TEST(ArrayTest, IsEmpty) {
  Array<int> array({0, 1, 2});
  EXPECT_FALSE(array.IsEmpty());

  array = Array<int>();
  EXPECT_TRUE(array.IsEmpty());
}

TEST(ArrayTest, GetItemAt) {
  Array<int> array;
  EXPECT_THROW(array.GetItemAt(0), std::out_of_range);
  EXPECT_THROW(array.GetItemAt(2), std::out_of_range);

  array = Array<int>({0, 1, 2});
  EXPECT_EQ(0, array.GetItemAt(0));
  EXPECT_EQ(1, array.GetItemAt(1));
  EXPECT_EQ(2, array.GetItemAt(2));
}

TEST(ArrayTest, Append) {
  Array<int> array =
      Array<int>({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15});
  array.Append(16);

  EXPECT_EQ(16, array.GetItemAt(16));
  EXPECT_EQ(17, array.GetSize());
  EXPECT_EQ(32, array.GetCapacity());
}

TEST(ArrayTest, Insert) {
  Array<int> array =
      Array<int>({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14});
  EXPECT_THROW(array.Insert(0, 16), std::out_of_range);

  array.Insert(0, 0);

  EXPECT_EQ(0, array.GetItemAt(0));
  EXPECT_EQ(16, array.GetSize());
  EXPECT_EQ(16, array.GetCapacity());

  array.Insert(0, 15);

  EXPECT_EQ(0, array.GetItemAt(15));
  EXPECT_EQ(14, array.GetItemAt(16));
  EXPECT_EQ(17, array.GetSize());
  EXPECT_EQ(32, array.GetCapacity());
}

TEST(ArrayTest, Prepend) {
  Array<int> array;
  EXPECT_THROW(array.Prepend(0), std::out_of_range);

  array = Array<int>({0, 1});
  array.Prepend(-1);
  EXPECT_EQ(-1, array.GetItemAt(0));
  EXPECT_EQ(0, array.GetItemAt(1));
  EXPECT_EQ(1, array.GetItemAt(2));
}

TEST(ArrayTest, Pop) {
  Array<int> array;
  EXPECT_THROW(array.Pop(), std::out_of_range);

  array =
      Array<int>({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
  EXPECT_EQ(16, array.Pop());
  EXPECT_EQ(16, array.GetSize());
  EXPECT_EQ(32, array.GetCapacity());
  EXPECT_EQ(15, array.GetItemAt(15));

  array.Pop();
  array.Pop();
  array.Pop();
  array.Pop();
  array.Pop();
  array.Pop();
  array.Pop();
  EXPECT_EQ(32, array.GetCapacity());
  array.Pop();
  EXPECT_EQ(16, array.GetCapacity());
}

TEST(ArrayTest, Delete) {
  Array<int> array({0, 1, 2});
  EXPECT_THROW(array.Delete(3), std::out_of_range);

  array.Delete(0);
  EXPECT_EQ(1, array.GetItemAt(0));
  EXPECT_EQ(2, array.GetItemAt(1));

  array.Delete(1);
  EXPECT_EQ(1, array.GetItemAt(0));

  array.Delete(0);
  EXPECT_TRUE(array.IsEmpty());
}

TEST(ArrayTest, Remove) {
  Array<int> array({0, 1, 2});

  array.Remove(-1);
  EXPECT_EQ(3, array.GetSize());
  EXPECT_EQ(0, array.GetItemAt(0));
  EXPECT_EQ(1, array.GetItemAt(1));
  EXPECT_EQ(2, array.GetItemAt(2));

  array.Remove(1);
  EXPECT_EQ(2, array.GetSize());
  EXPECT_EQ(0, array.GetItemAt(0));
  EXPECT_EQ(2, array.GetItemAt(1));
}

TEST(ArrayTest, Find) {
  Array<int> array({0, 1, 2});

  EXPECT_EQ(kIndexNotFound, array.Find(-1));
  EXPECT_EQ(0, array.Find(0));
  EXPECT_EQ(1, array.Find(1));
  EXPECT_EQ(2, array.Find(2));
}

}
