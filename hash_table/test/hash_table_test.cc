#include "hash_table/hash_table.h"
#include "gtest/gtest.h"

namespace {
using namespace td;

TEST(HashTableTest, SetGet) {
  HashTable<std::string, std::string> hash_table;
  hash_table.set("one", "one_value");
  hash_table.set("two", "two_value");
  hash_table.set("three", "three_value");
  hash_table.set("four", "four_value");

  EXPECT_EQ("one_value", hash_table.get("one"));
  EXPECT_EQ("two_value", hash_table.get("two"));
  EXPECT_EQ("three_value", hash_table.get("three"));
  EXPECT_EQ("four_value", hash_table.get("four"));

  EXPECT_EQ(nullptr, hash_table.get("five"));
}

TEST(HashTableTest, Remove) {
  HashTable<std::string, std::string> hash_table;
  hash_table.set("one", "one_value");
  hash_table.set("two", "two_value");
  hash_table.set("three", "three_value");
  hash_table.set("four", "four_value");

  hash_table.remove("three");
  hash_table.remove("two");
  hash_table.remove("four");
  hash_table.remove("five");

  EXPECT_EQ("one_value", hash_table.get("one"));
  EXPECT_EQ(nullptr, hash_table.get("four"));
  EXPECT_EQ(nullptr, hash_table.get("three"));
  EXPECT_EQ(nullptr, hash_table.get("two"));
}

}  // namespace