#include "priority_queue/priority_queue.h"
#include "gtest/gtest.h"

namespace {
using namespace td;

TEST(PriorityQueueTest, IsEmpty) {
  PriorityQueue<std::string> priority_queue(10);
  EXPECT_TRUE(priority_queue.is_empty());

  priority_queue.insert("c++", 1);
  EXPECT_FALSE(priority_queue.is_empty());
}

TEST(PriorityQueueTest, Size) {
  PriorityQueue<std::string> priority_queue(10);
  EXPECT_EQ(0, priority_queue.size());

  priority_queue.insert("c++", 1);
  EXPECT_EQ(1, priority_queue.size());

  priority_queue.insert("c", 2);
  EXPECT_EQ(2, priority_queue.size());
}

TEST(PriorityQueueTest, Max) {
  PriorityQueue<std::string> priority_queue(10);

  EXPECT_THROW(priority_queue.max(), std::out_of_range);

  priority_queue.insert("c++", 10);
  priority_queue.insert("c", 2);
  priority_queue.insert("swift", 5);
  priority_queue.insert("go", 15);
  priority_queue.insert("java", 1);

  EXPECT_EQ("go", priority_queue.max());
}

TEST(PriorityQueueTest, ExtractMax) {
  PriorityQueue<std::string> priority_queue(10);
  priority_queue.insert("c++", 10);
  priority_queue.insert("c", 2);
  priority_queue.insert("swift", 5);
  priority_queue.insert("go", 15);
  priority_queue.insert("java", 1);

  EXPECT_EQ("go", priority_queue.extract_max());
  EXPECT_EQ("c++", priority_queue.extract_max());
  EXPECT_EQ("swift", priority_queue.extract_max());
  EXPECT_EQ("c", priority_queue.extract_max());
  EXPECT_EQ("java", priority_queue.extract_max());

  EXPECT_THROW(priority_queue.extract_max(), std::out_of_range);
}

TEST(PriorityQueueTest, Update) {
  PriorityQueue<std::string> priority_queue(10);
  priority_queue.insert("c++", 10);
  priority_queue.insert("c", 2);
  priority_queue.insert("swift", 5);
  priority_queue.insert("go", 15);
  priority_queue.insert("java", 1);

  priority_queue.update("R", 100);
  priority_queue.update("c", 20);

  EXPECT_EQ("c", priority_queue.max());
}

TEST(PriorityQueueTest, Insert) {
  PriorityQueue<std::string> priority_queue(10);
  priority_queue.insert("c++", 10);
  priority_queue.insert("c", 2);
  priority_queue.insert("swift", 5);
  priority_queue.insert("go", 15);
  priority_queue.insert("go", 15);
  priority_queue.insert("java", 1);
  priority_queue.insert("swift", 5);

  EXPECT_EQ(7, priority_queue.size());

  EXPECT_EQ("go", priority_queue.extract_max());
  EXPECT_EQ("go", priority_queue.extract_max());
  EXPECT_EQ("c++", priority_queue.extract_max());
  EXPECT_EQ("swift", priority_queue.extract_max());
  EXPECT_EQ("swift", priority_queue.extract_max());
  EXPECT_EQ("c", priority_queue.extract_max());
  EXPECT_EQ("java", priority_queue.extract_max());
}

TEST(PriorityQueueTest, Remove) {
  PriorityQueue<std::string> priority_queue(10);

  priority_queue.remove("R");

  priority_queue.insert("c++", 10);
  priority_queue.insert("c", 2);
  priority_queue.insert("swift", 5);
  priority_queue.insert("go", 15);
  priority_queue.insert("java", 1);

  priority_queue.remove("swift");
  EXPECT_EQ(4, priority_queue.size());

  priority_queue.remove("c++");
  EXPECT_EQ(3, priority_queue.size());

  EXPECT_EQ("go", priority_queue.extract_max());
  EXPECT_EQ("c", priority_queue.extract_max());
  EXPECT_EQ("java", priority_queue.extract_max());
}

}  // namespace
