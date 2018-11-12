#pragma once

#include <string>

#include "utils/macros.h"
#include "utils/utils.h"

namespace td {

// Capacity of hash table after it's initialized
constexpr int default_capacity = 11;

// Key and value of the null node
constexpr char null_node_key[] = "HashTable::Node::null::key";
constexpr char null_node_value[] = "HashTable::Node::null::value";

// Key and value of the dummy node
constexpr char dummy_node_key[] = "HashTable::Node::dummy::key";
constexpr char dummy_node_value[] = "HashTable::Node::dummy::value";

constexpr float growth_factor = 0.5f;
constexpr float shrink_factor = 0.2f;

// A hash table template with std::string key type.
template <typename ValueType>
class HashTable {
 public:
  HashTable();
  ~HashTable();

  // Add the given key and value to hash table. If key exists, replace old value
  // with given value
  void set(const std::string& key, const ValueType& value);

  // Returns value at given key. If key doesn't exist, return value of null node
  ValueType get(const std::string& key);

  // Removes value at given key. If key doesn't exist, does nothing
  void remove(const std::string& key);

 private:
  // Node's data type
  struct Node {
    std::string key;
    ValueType value;

    Node() = default;
    Node(const std::string& k, const ValueType& v) : key(k), value(v) {}

    static Node null();
    bool is_null();

    static Node dummy();
    bool is_dummy();
  };

  // Bases on given key to return a non-negative number smaller than given
  // capacity
  std::size_t hash(const std::string& key, std::size_t capacity);

  // Growth: If |new_size| is greater than |capacity_ * growth_factor|, allocate
  // |table_| with capacity is smallest prime which is greater or equal than
  // double current capacity.
  //
  // Shink: If |new_size| is less than |capacity_ * shrink_factor|,  allocate
  // |table_| with capacity is smallest prime which is greater or equal than
  // half of current capacity (new capacity is always greater than
  // default_capacity).
  void reallocate_if_needed(std::size_t new_size);

  // Represent size of |table_|, should be a prime
  std::size_t capacity_{default_capacity};

  // Number of items are currently stored in hash table.
  std::size_t size_{0};

  // Raw array where items are stored.
  Node* table_{new Node[capacity_]};

  DISALLOW_COPY_AND_ASSIGN(HashTable);
};

}  // namespace td

/****************  Hash table implementation ****************/
namespace td {

// Public

template <typename ValueType>
HashTable<ValueType>::HashTable() {
  for (std::size_t i = 0; i < capacity_; ++i) {
    table_[i] = Node::null();
  }
}

template <typename ValueType>
HashTable<ValueType>::~HashTable() {
  delete[] table_;
}

template <typename ValueType>
void HashTable<ValueType>::set(const std::string& key, const ValueType& value) {
  if (get(key) == null_node_value)
    reallocate_if_needed(++size_);

  std::size_t hash_value = hash(key, capacity_);
  while (!table_[hash_value].is_null() && !table_[hash_value].is_dummy() &&
         table_[hash_value].key != key)
    hash_value = (hash_value + 1) % capacity_;

  table_[hash_value] = Node(key, value);
}

template <typename ValueType>
ValueType HashTable<ValueType>::get(const std::string& key) {
  std::size_t hash_value = hash(key, capacity_);
  while (table_[hash_value].is_dummy() ||
         (!table_[hash_value].is_null() && table_[hash_value].key != key))
    hash_value = (hash_value + 1) % capacity_;
  return table_[hash_value].value;
}

template <typename ValueType>
void HashTable<ValueType>::remove(const std::string& key) {
  if (get(key) == null_node_value)
    return;

  reallocate_if_needed(--size_);

  std::size_t hash_value = hash(key, capacity_);
  while (table_[hash_value].is_dummy() ||
         (!table_[hash_value].is_null() && table_[hash_value].key != key))
    hash_value = (hash_value + 1) % capacity_;

  if (!table_[hash_value].is_null())
    table_[hash_value] = Node::dummy();
}

// Private

// http://www.cse.yorku.ca/~oz/hash.html
// djb2 algorithm
template <typename ValueType>
std::size_t HashTable<ValueType>::hash(const std::string& key,
                                       std::size_t capacity) {
  unsigned long hash = 5381;
  for (std::size_t i = 0; i < key.length(); ++i)
    hash = hash * 33 + key[i];
  return hash % capacity;
}

template <typename ValueType>
void HashTable<ValueType>::reallocate_if_needed(std::size_t new_size) {
  std::size_t new_capacity = default_capacity;

  // Decide |table_| should be allocated or not
  if (new_size > capacity_ * growth_factor) {
    new_capacity = utils::next_prime(capacity_ * 2);
  } else if (new_size < capacity_ * shrink_factor) {
    new_capacity = utils::next_prime(capacity_ / 2);
    new_capacity = new_capacity > default_capacity ? new_capacity : default_capacity;
  } else {
    return;
  }

  // Does nothing if capacity doesn't change
  if (new_capacity == capacity_)
    return;

  // Allocate a table with new capacity and fill it with null nodes
  Node* new_table = new Node[new_capacity];
  for (std::size_t i = 0; i < new_capacity; ++i) {
    new_table[i] = Node::null();
  }

  // Move valid nodes from current table to new table and rehash them.
  for (std::size_t i = 0; i < capacity_; ++i) {
    if (!table_[i].is_null() && !table_[i].is_dummy()) {
      std::size_t hash_value = hash(table_[i].key, new_capacity);
      while (!new_table[hash_value].is_null())
        hash_value = (hash_value + 1) % new_capacity;
      new_table[hash_value] = table_[i];
    }
  }

  // Clean up and finish
  delete[] table_;
  table_ = new_table;
  capacity_ = new_capacity;
}

// Node
template <typename ValueType>
typename HashTable<ValueType>::Node HashTable<ValueType>::Node::null() {
  return HashTable::Node(null_node_key, null_node_value);
}

template <typename ValueType>
bool HashTable<ValueType>::Node::is_null() {
  return key == null_node_key;
}

template <typename ValueType>
typename HashTable<ValueType>::Node HashTable<ValueType>::Node::dummy() {
  return HashTable::Node(dummy_node_key, null_node_value);
}

template <typename ValueType>
bool HashTable<ValueType>::Node::is_dummy() {
  return key == dummy_node_key;
}

}  // namespace td

