#include "linked_list/linked_list.h"
#include "gtest/gtest.h"

namespace {
using namespace td;

TEST(LinkedListTest, DefaultConstructor) {
  LinkedList<int> linked_list;
  EXPECT_EQ(0, linked_list.size());
}

TEST(LinkedListTest, SingleValueConstructor) {
  LinkedList<int> linked_list(0);
  EXPECT_EQ(1, linked_list.size());
  EXPECT_EQ(0, linked_list.value_at(0));

  linked_list = LinkedList<int>(4);
  EXPECT_EQ(4, linked_list.value_at(0));
}

TEST(LinkedListTest, InitializerListConstructor) {
  LinkedList<int> linked_list({10, 12, 14, 16, 18});
  EXPECT_EQ(5, linked_list.size());
  EXPECT_EQ(10, linked_list.value_at(0));
  EXPECT_EQ(12, linked_list.value_at(1));
  EXPECT_EQ(14, linked_list.value_at(2));
  EXPECT_EQ(16, linked_list.value_at(3));
  EXPECT_EQ(18, linked_list.value_at(4));
}

TEST(LinkedListTest, CopyConstructor) {
  LinkedList<int> original_linked_list({0, 1, 2});

  LinkedList<int> copy_linked_list(original_linked_list);
  EXPECT_EQ(3, copy_linked_list.size());
  EXPECT_EQ(0, copy_linked_list.value_at(0));
  EXPECT_EQ(1, copy_linked_list.value_at(1));
  EXPECT_EQ(2, copy_linked_list.value_at(2));

  original_linked_list.push_front(-1);
  EXPECT_EQ(3, copy_linked_list.size());
  EXPECT_EQ(0, copy_linked_list.value_at(0));
  EXPECT_EQ(1, copy_linked_list.value_at(1));
  EXPECT_EQ(2, copy_linked_list.value_at(2));
}

TEST(LinkedListTest, MoveConstructor) {
  LinkedList<int> tmp_linked_list({1, 2, 3});

  LinkedList<int> linked_list(std::move(tmp_linked_list));
  EXPECT_EQ(3, linked_list.size());
  EXPECT_EQ(1, linked_list.value_at(0));
  EXPECT_EQ(2, linked_list.value_at(1));
  EXPECT_EQ(3, linked_list.value_at(2));

  EXPECT_EQ(0, tmp_linked_list.size());
}

TEST(LinkedListTest, CopyOperator) {
  LinkedList<int> tmp_linked_list({0, 1, 2});

  LinkedList<int> linked_list;
  linked_list = tmp_linked_list;

  EXPECT_EQ(3, linked_list.size());
  EXPECT_EQ(0, linked_list.value_at(0));
  EXPECT_EQ(1, linked_list.value_at(1));
  EXPECT_EQ(2, linked_list.value_at(2));

  linked_list.remove_at(0);
  EXPECT_EQ(2, linked_list.size());
  EXPECT_EQ(1, linked_list.value_at(0));
  EXPECT_EQ(2, linked_list.value_at(1));

  EXPECT_EQ(3, tmp_linked_list.size());
  EXPECT_EQ(0, tmp_linked_list.value_at(0));
  EXPECT_EQ(1, tmp_linked_list.value_at(1));
  EXPECT_EQ(2, tmp_linked_list.value_at(2));
}

TEST(LinkedListTest, MoveOperator) {
  LinkedList<int> linked_list = LinkedList<int>({0, 1, 2});
  EXPECT_EQ(3, linked_list.size());
  EXPECT_EQ(0, linked_list.value_at(0));
  EXPECT_EQ(1, linked_list.value_at(1));
  EXPECT_EQ(2, linked_list.value_at(2));
}

TEST(LinkedListTest, Size) {
  LinkedList<int> linked_list;

  EXPECT_EQ(0, linked_list.size());

  linked_list.push_front(0);
  EXPECT_EQ(1, linked_list.size());

  linked_list.push_front(1);
  linked_list.push_front(2);
  EXPECT_EQ(3, linked_list.size());
}

TEST(LinkedListTest, IsEmpty) {
  LinkedList<int> linked_list;

  EXPECT_TRUE(linked_list.is_empty());

  linked_list = LinkedList<int>(1);
  EXPECT_FALSE(linked_list.is_empty());
}

TEST(LinkedListTest, ValueAt) {
  LinkedList<int> linked_list({9, 10, 12, 14, 16, 0});
  EXPECT_EQ(9, linked_list.value_at(0));
  EXPECT_EQ(10, linked_list.value_at(1));
  EXPECT_EQ(12, linked_list.value_at(2));
  EXPECT_EQ(14, linked_list.value_at(3));
  EXPECT_EQ(16, linked_list.value_at(4));
  EXPECT_EQ(0, linked_list.value_at(5));

  EXPECT_THROW(linked_list.value_at(6), std::out_of_range);
  EXPECT_THROW(linked_list.value_at(10), std::out_of_range);
}

TEST(LinkedListTest, PushFront) {
  LinkedList<int> linked_list(2);

  linked_list.push_front(10);
  EXPECT_EQ(10, linked_list.value_at(0));
  EXPECT_EQ(2, linked_list.value_at(1));

  linked_list.push_front(1);
  EXPECT_EQ(1, linked_list.value_at(0));
  EXPECT_EQ(10, linked_list.value_at(1));
  EXPECT_EQ(2, linked_list.value_at(2));
}

TEST(LinkedListTest, PopFront) {
  LinkedList<int> linked_list;
  EXPECT_THROW(linked_list.pop_front(), std::out_of_range);

  linked_list = LinkedList<int>({8, 7, 2, 4, 6});

  EXPECT_EQ(8, linked_list.pop_front());
  EXPECT_EQ(4, linked_list.size());
  EXPECT_EQ(7, linked_list.value_at(0));
  EXPECT_EQ(2, linked_list.value_at(1));
  EXPECT_EQ(4, linked_list.value_at(2));
  EXPECT_EQ(6, linked_list.value_at(3));

  EXPECT_EQ(7, linked_list.pop_front());
  EXPECT_EQ(2, linked_list.pop_front());
  EXPECT_EQ(2, linked_list.size());
  EXPECT_EQ(4, linked_list.value_at(0));
  EXPECT_EQ(6, linked_list.value_at(1));
}

TEST(LinkedListTest, PushBack) {
  LinkedList<int> linked_list({1, 2, 3, 4});

  linked_list.push_back(0);
  EXPECT_EQ(5, linked_list.size());
  EXPECT_EQ(0, linked_list.value_at(4));
  EXPECT_EQ(1, linked_list.value_at(0));

  linked_list.push_back(1);
  linked_list.push_back(2);
  linked_list.push_back(3);
  EXPECT_EQ(8, linked_list.size());
  EXPECT_EQ(3, linked_list.value_at(7));
}

TEST(LinkedListTest, PopBack) {
  LinkedList<int> linked_list;
  EXPECT_THROW(linked_list.pop_back(), std::out_of_range);

  linked_list = LinkedList<int>({1, 2, 3, 4});

  EXPECT_EQ(4, linked_list.pop_back());
  EXPECT_EQ(3, linked_list.size());
  EXPECT_EQ(1, linked_list.value_at(0));
  EXPECT_EQ(2, linked_list.value_at(1));
  EXPECT_EQ(3, linked_list.value_at(2));

  EXPECT_EQ(3, linked_list.pop_back());
  EXPECT_EQ(2, linked_list.pop_back());
  EXPECT_EQ(1, linked_list.size());
}

TEST(LinkedListTest, Front) {
  LinkedList<int> linked_list;
  EXPECT_THROW(linked_list.front(), std::out_of_range);

  linked_list = LinkedList<int>({1, 2, 3, 4});
  EXPECT_EQ(1, linked_list.front());

  linked_list = LinkedList<int>({0});
  EXPECT_EQ(0, linked_list.front());
}

TEST(LinkedListTest, Back) {
  LinkedList<int> linked_list;
  EXPECT_THROW(linked_list.back(), std::out_of_range);

  linked_list = LinkedList<int>({1, 2, 3, 4});
  EXPECT_EQ(4, linked_list.back());

  linked_list = LinkedList<int>({0});
  EXPECT_EQ(0, linked_list.back());
}

TEST(LinkedListTest, Insert) {
  LinkedList<int> linked_list;

  linked_list.insert(1, 0);
  EXPECT_EQ(1, linked_list.size());
  EXPECT_EQ(1, linked_list.value_at(0));

  linked_list = LinkedList<int>({1, 2, 3});

  linked_list.insert(10, 2);
  EXPECT_EQ(4, linked_list.size());
  EXPECT_EQ(1, linked_list.value_at(0));
  EXPECT_EQ(2, linked_list.value_at(1));
  EXPECT_EQ(10, linked_list.value_at(2));
  EXPECT_EQ(3, linked_list.value_at(3));

  linked_list.insert(8, 2);
  linked_list.insert(0, 1);
  EXPECT_EQ(6, linked_list.size());
  EXPECT_EQ(1, linked_list.value_at(0));
  EXPECT_EQ(0, linked_list.value_at(1));
  EXPECT_EQ(2, linked_list.value_at(2));
  EXPECT_EQ(8, linked_list.value_at(3));
  EXPECT_EQ(10, linked_list.value_at(4));
  EXPECT_EQ(3, linked_list.value_at(5));
}

TEST(LinkedListTest, RemoveAt) {
  LinkedList<int> linked_list = LinkedList<int>({1, 2, 3, 4, 5});

  linked_list.remove_at(1);
  EXPECT_EQ(4, linked_list.size());
  EXPECT_EQ(1, linked_list.value_at(0));
  EXPECT_EQ(3, linked_list.value_at(1));
  EXPECT_EQ(4, linked_list.value_at(2));
  EXPECT_EQ(5, linked_list.value_at(3));

  linked_list.remove_at(3);
  linked_list.remove_at(0);
  EXPECT_EQ(2, linked_list.size());
  EXPECT_EQ(3, linked_list.value_at(0));
  EXPECT_EQ(4, linked_list.value_at(1));

  EXPECT_THROW(linked_list.remove_at(3), std::out_of_range);
}

TEST(LinkedListTest, Remove) {
  LinkedList<int> linked_list = LinkedList<int>({1, 2, 3, 4, 5});

  linked_list.remove(4);
  EXPECT_EQ(4, linked_list.size());
  EXPECT_EQ(1, linked_list.value_at(0));
  EXPECT_EQ(2, linked_list.value_at(1));
  EXPECT_EQ(3, linked_list.value_at(2));
  EXPECT_EQ(5, linked_list.value_at(3));

  linked_list.remove(2);
  linked_list.remove(5);
  linked_list.remove(10);
  EXPECT_EQ(2, linked_list.size());
  EXPECT_EQ(1, linked_list.value_at(0));
  EXPECT_EQ(3, linked_list.value_at(1));
}

TEST(LinkedListTest, ValueFromBack) {
  LinkedList<int> linked_list = LinkedList<int>({1, 2, 3, 4, 5});

  EXPECT_EQ(5, linked_list.value_from_back(0));
  EXPECT_EQ(4, linked_list.value_from_back(1));
  EXPECT_EQ(3, linked_list.value_from_back(2));
  EXPECT_EQ(2, linked_list.value_from_back(3));
  EXPECT_EQ(1, linked_list.value_from_back(4));

  EXPECT_THROW(linked_list.value_from_back(5), std::out_of_range);
}

TEST(LinkedListTest, Reverse) {
  LinkedList<int> linked_list = LinkedList<int>({1, 2, 3, 4, 5});

  linked_list.reverse();

  EXPECT_EQ(5, linked_list.size());
  EXPECT_EQ(5, linked_list.value_at(0));
  EXPECT_EQ(4, linked_list.value_at(1));
  EXPECT_EQ(3, linked_list.value_at(2));
  EXPECT_EQ(2, linked_list.value_at(3));
  EXPECT_EQ(1, linked_list.value_at(4));
}

}  // namespace
