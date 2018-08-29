#pragma once

#include <iostream>

namespace td {

template <typename T>
class LinkedList {
 public:
  LinkedList() = default;
  LinkedList(const T& value);
  LinkedList(std::initializer_list<T> il);

  LinkedList(const LinkedList<T>& other);
  LinkedList(LinkedList<T>&& other);

  LinkedList<T>& operator=(const LinkedList<T>& other);
  LinkedList<T>& operator=(LinkedList<T>&& other);

  ~LinkedList();

  // Return number of nodes are currently stored in list.
  std::size_t size();

  // Determine list is empty or not.
  bool is_empty();

  // Return value of node at given index.
  T value_at(std::size_t index);

  // Add a node with |value| to the front of list.
  void push_front(const T& value);

  // Remove front node and return its value.
  T pop_front();

  // Add a node with |value| to the end of list.
  void push_back(const T& value);

  // Remove end node and return its value.
  T pop_back();

  // Return value of front node.
  T front();

  // Return value of end node.
  T back();

  // Insert a node with |value| at |index|.
  // New node will point to current node at |index|.
  void insert(const T& value, std::size_t index);

  // Remove node at given index.
  void remove_at(std::size_t index);

  // Remove first node in list with given value.
  void remove(const T& value);

  // Return value of node at |index| from the end of list.
  T value_from_back(std::size_t index);

  // Reverse list
  void reverse();

  // Swap value inside |lhs| and |rhs|
  friend void swap<T>(SLinkedList<T>& lhs, SLinkedList<T>& rhs);
};

}  // namespace td