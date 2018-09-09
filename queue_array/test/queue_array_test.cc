#include "queue_array/queue_array.h"
#include "gtest/gtest.h"

namespace {
using namespace td;

TEST(QueueLinkedListTest, IsEmpty) {
  Queue<int> queue;
  EXPECT_TRUE(queue.is_empty());

  queue.enqueue(1);
  EXPECT_FALSE(queue.is_empty());
}

TEST(QueueLinkedListTest, IsFull) {
  Queue<int> queue(3);
  EXPECT_FALSE(queue.is_full());

  queue.enqueue(1);
  EXPECT_FALSE(queue.is_full());

  queue.enqueue(2);
  EXPECT_FALSE(queue.is_full());

  queue.enqueue(3);
  EXPECT_TRUE(queue.is_full());
}

TEST(QueueLinkedListTest, Enqueue) {
  Queue<int> queue(3);

  queue.enqueue(1);
  queue.enqueue(2);
  queue.enqueue(3);
  queue.enqueue(4);
  EXPECT_EQ(1, queue.dequeue());
  EXPECT_EQ(2, queue.dequeue());
  EXPECT_EQ(3, queue.dequeue());
  EXPECT_TRUE(queue.is_empty());
}

TEST(QueueLinkedListTest, Dequeue) {
  Queue<int> queue(2);

  EXPECT_THROW(queue.dequeue(), std::out_of_range);

  queue.enqueue(1);
  queue.enqueue(2);
  queue.enqueue(3);
  queue.enqueue(4);
  queue.enqueue(5);

  EXPECT_EQ(1, queue.dequeue());
  EXPECT_EQ(2, queue.dequeue());
  EXPECT_THROW(queue.dequeue(), std::out_of_range);
  EXPECT_TRUE(queue.is_empty());
}

}  // namespace
