#include "queue_linked_list/queue_linked_list.h"
#include "gtest/gtest.h"

namespace {
using namespace td;

TEST(QueueLinkedListTest, IsEmpty) {
  Queue<int> queue;
  EXPECT_TRUE(queue.is_empty());

  queue.enqueue(1);
  EXPECT_FALSE(queue.is_empty());
}

TEST(QueueLinkedListTest, Enqueue) {
  Queue<int> queue;

  queue.enqueue(1);
  queue.enqueue(2);
  queue.enqueue(3);
  EXPECT_EQ(1, queue.dequeue());
  EXPECT_EQ(2, queue.dequeue());

  queue.dequeue();
  EXPECT_TRUE(queue.is_empty());
}

TEST(QueueLinkedListTest, Dequeue) {
  Queue<int> queue;

  EXPECT_THROW(queue.dequeue(), std::out_of_range);

  queue.enqueue(1);
  queue.enqueue(2);
  queue.enqueue(3);
  queue.enqueue(4);
  queue.enqueue(5);

  EXPECT_EQ(1, queue.dequeue());
  EXPECT_EQ(2, queue.dequeue());
  EXPECT_EQ(3, queue.dequeue());
  EXPECT_EQ(4, queue.dequeue());
  EXPECT_EQ(5, queue.dequeue());
  EXPECT_TRUE(queue.is_empty());
}

}  // namespace
