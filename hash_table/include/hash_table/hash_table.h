#pragma once

#include <iostream>

#include "utils/macros.h"

namespace td {

// Bases on given key to returns a non-negative number smaller than given size
template <typename KeyType>
std::size_t hash(const KeyType& key, std::size_t size);

// A hash table template
template <typename KeyType, typename ValueType>
class HashTable {
 public:
  HashTable() = default;
  ~HashTable();

  // Add the given key and value to hash table. If key exists, replace old value with given value
  void set(const KeyType& key, const ValueType& value);

  // Returns value at given key. If key doesn't exist, return nullptr
  ValueType get(const KeyType& key);

  // Removes value at given key. If key doesn't exist, does nothing
  void remove(const KeyType& key);

 private:
  // Node's data type
  struct Node {
    KeyType key;
    ValueType value;
  };

  // Represent size of |table_|
  std::size_t capacity_;

  // Number of items are currently stored in hash table.
  std::size_t size_;

  // Raw array where items are stored.
  Node* table_;

  DISALLOW_COPY_AND_ASSIGN(HashTable);
};

}  // namespace td