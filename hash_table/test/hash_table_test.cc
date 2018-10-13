#include "hash_table/hash_table.h"
#include "gtest/gtest.h"

namespace {
using namespace td;

TEST(HashTableTest, SetGet) {
  HashTable<std::string> hash_table;
  hash_table.set("1", "1v");
  hash_table.set("2", "2v");
  hash_table.set("3", "3v");
  hash_table.set("4", "4v");
  hash_table.set("5", "5v");
  hash_table.set("6", "6v");
  hash_table.set("7", "7v");
  hash_table.set("8", "8v");
  hash_table.set("9", "9v");
  hash_table.set("10", "10v");
  hash_table.set("11", "11v");
  hash_table.set("12", "12v");
  hash_table.set("13", "13v");
  hash_table.set("14", "14v");

  EXPECT_EQ("1v", hash_table.get("1"));
  EXPECT_EQ("2v", hash_table.get("2"));
  EXPECT_EQ("3v", hash_table.get("3"));
  EXPECT_EQ("4v", hash_table.get("4"));
  EXPECT_EQ("5v", hash_table.get("5"));
  EXPECT_EQ("6v", hash_table.get("6"));
  EXPECT_EQ("7v", hash_table.get("7"));
  EXPECT_EQ("8v", hash_table.get("8"));
  EXPECT_EQ("9v", hash_table.get("9"));
  EXPECT_EQ("10v", hash_table.get("10"));
  EXPECT_EQ("11v", hash_table.get("11"));
  EXPECT_EQ("12v", hash_table.get("12"));
  EXPECT_EQ("13v", hash_table.get("13"));
  EXPECT_EQ("14v", hash_table.get("14"));

  EXPECT_EQ(null_node_value, hash_table.get("hello"));
  EXPECT_EQ(null_node_value, hash_table.get("hi"));

  hash_table.set("15", "15v");
  hash_table.set("16", "16v");
  hash_table.set("17", "17v");
  hash_table.set("18", "18v");
  hash_table.set("19", "19v");

  EXPECT_EQ("15v", hash_table.get("15"));
  EXPECT_EQ("16v", hash_table.get("16"));
  EXPECT_EQ("17v", hash_table.get("17"));
  EXPECT_EQ("18v", hash_table.get("18"));
  EXPECT_EQ("19v", hash_table.get("19"));

  hash_table.set("2", "22v");
  EXPECT_EQ("22v", hash_table.get("2"));
}

TEST(HashTableTest, Remove) {
  HashTable<std::string> hash_table;
  hash_table.set("1", "1v");
  hash_table.set("2", "2v");
  hash_table.set("3", "3v");
  hash_table.set("4", "4v");
  hash_table.set("5", "5v");
  hash_table.set("6", "6v");
  hash_table.set("7", "7v");
  hash_table.set("8", "8v");
  hash_table.set("9", "9v");
  hash_table.set("10", "10v");
  hash_table.set("11", "11v");
  hash_table.set("12", "12v");
  hash_table.set("13", "13v");
  hash_table.set("14", "14v");

  hash_table.remove("5");
  EXPECT_EQ("1v", hash_table.get("1"));
  EXPECT_EQ("2v", hash_table.get("2"));
  EXPECT_EQ("3v", hash_table.get("3"));
  EXPECT_EQ("4v", hash_table.get("4"));
  EXPECT_EQ("6v", hash_table.get("6"));
  EXPECT_EQ("7v", hash_table.get("7"));
  EXPECT_EQ("8v", hash_table.get("8"));
  EXPECT_EQ("9v", hash_table.get("9"));
  EXPECT_EQ("10v", hash_table.get("10"));
  EXPECT_EQ("11v", hash_table.get("11"));
  EXPECT_EQ("12v", hash_table.get("12"));
  EXPECT_EQ("13v", hash_table.get("13"));
  EXPECT_EQ("14v", hash_table.get("14"));

  hash_table.remove("2");
  EXPECT_EQ("1v", hash_table.get("1"));
  EXPECT_EQ("3v", hash_table.get("3"));
  EXPECT_EQ("4v", hash_table.get("4"));
  EXPECT_EQ("6v", hash_table.get("6"));
  EXPECT_EQ("7v", hash_table.get("7"));
  EXPECT_EQ("8v", hash_table.get("8"));
  EXPECT_EQ("9v", hash_table.get("9"));
  EXPECT_EQ("10v", hash_table.get("10"));
  EXPECT_EQ("11v", hash_table.get("11"));
  EXPECT_EQ("12v", hash_table.get("12"));
  EXPECT_EQ("13v", hash_table.get("13"));
  EXPECT_EQ("14v", hash_table.get("14"));

  hash_table.remove("9");
  hash_table.remove("1");
  hash_table.remove("2");
  hash_table.remove("3");
  hash_table.remove("4");
  hash_table.remove("5");
  hash_table.remove("6");
  hash_table.remove("7");
  hash_table.remove("8");
  hash_table.remove("9");
  hash_table.remove("10");
  hash_table.remove("11");
  hash_table.remove("12");

  EXPECT_EQ("13v", hash_table.get("13"));
  EXPECT_EQ("14v", hash_table.get("14"));

  EXPECT_EQ(null_node_value, hash_table.get("1"));
}

}  // namespace

