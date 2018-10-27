#pragma once

#include <iostream>

#include "utils/utils.h"

namespace td {

template <typename DataType>
class LinkedList;

template <typename DataType>
void swap(LinkedList<DataType>& rhs, LinkedList<DataType>& lhs);

// A linked list template
template <typename DataType>
class LinkedList {
 public:
  LinkedList() = default;
  LinkedList(const DataType& value);
  LinkedList(std::initializer_list<DataType> il);

  LinkedList(const LinkedList<DataType>& other);
  LinkedList(LinkedList<DataType>&& other);

  LinkedList<DataType>& operator=(const LinkedList<DataType>& other);
  LinkedList<DataType>& operator=(LinkedList<DataType>&& other);

  ~LinkedList();

  // Return number of nodes are currently stored in list.
  std::size_t size();

  // Determine list is empty or not.
  bool is_empty();

  // Return value of node at given index.
  DataType value_at(std::size_t index);

  // Add a node with |value| to the front of list.
  void push_front(const DataType& value);

  // Remove front node and return its value.
  DataType pop_front();

  // Add a node with |value| to the end of list.
  void push_back(const DataType& value);

  // Remove last node and return its value.
  DataType pop_back();

  // Return value of front node.
  DataType front();

  // Return value of last node.
  DataType back();

  // Insert a node with |value| at |index|.
  void insert(const DataType& value, std::size_t index);

  // Remove node at given index.
  void remove_at(std::size_t index);

  // Remove first node in list with given value.
  void remove(const DataType& value);

  // Return value of node at |index| from the end of list.
  DataType value_from_back(std::size_t index);

  // Reverse list
  void reverse();

  // Swap values inside |lhs| and |rhs|.
  // Follow copy-and-swap idiom
  // https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
  friend void swap<DataType>(LinkedList<DataType>& lhs,
                             LinkedList<DataType>& rhs);

 private:
  // Node's data type
  struct Node {
    DataType data;
    Node* next{nullptr};

    Node(const DataType& d) : data(d) {}
    Node(const DataType& d, Node* n) : data(d), next(n) {}
  };

  // Pointer points to the first node in list.
  Node* head_{nullptr};

  // Number of nodes are currently stored in list.
  int size_{0};

  // Release all nodes in list, assign nullptr to |head_|
  void release_head();
};

}  // namespace td

/****************  Linked List implmentation ****************/
namespace td {

template <typename DataType>
void swap(LinkedList<DataType>& lhs, LinkedList<DataType>& rhs) {
  using std::swap;

  swap(lhs.head_, rhs.head_);
  swap(lhs.size_, rhs.size_);
}

// Public
template <typename DataType>
LinkedList<DataType>::LinkedList(const DataType& value)
    : head_(new Node(value)), size_(1) {}

template <typename DataType>
LinkedList<DataType>::LinkedList(std::initializer_list<DataType> il) {
  for (int i = il.size() - 1; i >= 0; --i) {
    push_front(il.begin()[i]);
  }
}

template <typename DataType>
LinkedList<DataType>::LinkedList(const LinkedList<DataType>& other)
    : size_(other.size_) {
  release_head();

  Node* other_head = other.head_;
  Node** pp_tail = &head_;

  while (other_head) {
    *pp_tail = new Node(other_head->data);
    pp_tail = &(*pp_tail)->next;
    other_head = other_head->next;
  }
}

template <typename DataType>
LinkedList<DataType>::LinkedList(LinkedList<DataType>&& other)
    : head_(other.head_), size_(other.size_) {
  other.head_ = nullptr;
  other.size_ = 0;
}

template <typename DataType>
LinkedList<DataType>& LinkedList<DataType>::operator=(
    const LinkedList<DataType>& other) {
  LinkedList<DataType> temp(other);
  swap(*this, temp);
  return *this;
}

template <typename DataType>
LinkedList<DataType>& LinkedList<DataType>::operator=(
    LinkedList<DataType>&& other) {
  // Maybe shouldn't use |swap| method for move assignment operator
  // https://stackoverflow.com/questions/6687388/why-do-some-people-use-swap-for-move-assignments
  LinkedList<DataType> temp = std::move(other);
  swap(*this, temp);
  return *this;
}

template <typename DataType>
LinkedList<DataType>::~LinkedList() {
  size_ = 0;
  release_head();
}

template <typename DataType>
std::size_t LinkedList<DataType>::size() {
  return size_;
}

template <typename DataType>
bool LinkedList<DataType>::is_empty() {
  return size_ == 0;
}

template <typename DataType>
DataType LinkedList<DataType>::value_at(std::size_t index) {
  utils::validate(index, size_, utils::Action::kNone);

  Node* target_node = head_;
  for (std::size_t i = 0; i < index; ++i) {
    target_node = target_node->next;
  }
  return target_node->data;
}

template <typename DataType>
void LinkedList<DataType>::push_front(const DataType& value) {
  ++size_;

  Node* current_head = head_;
  head_ = new Node(value);
  head_->next = current_head;
}

template <typename DataType>
DataType LinkedList<DataType>::pop_front() {
  utils::validate(0, size_--, utils::Action::kRemoved);

  // Get returned data
  Node* removed_node = head_;
  DataType data = removed_node->data;

  // Remove first node
  head_ = head_->next;

  // Clean up
  delete removed_node;

  return data;
}

template <typename DataType>
void LinkedList<DataType>::push_back(const DataType& value) {
  // Get last node
  Node** pp_node = &head_;
  while (*pp_node) {
    pp_node = &(*pp_node)->next;
  }

  // Add new node to the end of list
  *pp_node = new Node(value);
  ++size_;
}

template <typename DataType>
DataType LinkedList<DataType>::pop_back() {
  std::size_t last_index = size_ - 1;
  utils::validate(last_index, size_--, utils::Action::kRemoved);

  // Get last node
  Node** pp_tail_node = &head_;
  while ((*pp_tail_node)->next) {
    pp_tail_node = &(*pp_tail_node)->next;
  }
  Node* tail_node = *pp_tail_node;

  // Get returned data
  DataType data = tail_node->data;

  // Remove last node
  *pp_tail_node = nullptr;

  // Clean up
  delete tail_node;

  return data;
}

template <typename DataType>
DataType LinkedList<DataType>::front() {
  return value_at(0);
}

template <typename DataType>
DataType LinkedList<DataType>::back() {
  return value_at(size_ - 1);
}

template <typename DataType>
void LinkedList<DataType>::insert(const DataType& value, std::size_t index) {
  utils::validate(index, size_++, utils::Action::kInserted);

  // Find node at given index
  Node** pp_node = &head_;
  while (index > 0) {
    pp_node = &(*pp_node)->next;
    --index;
  }

  // Insert new node to the list
  Node* new_node = new Node(value, *pp_node);
  *pp_node = new_node;
}

template <typename DataType>
void LinkedList<DataType>::remove_at(std::size_t index) {
  utils::validate(index, size_--, utils::Action::kRemoved);

  // Find removed node
  Node** pp_node = &head_;
  while (index > 0) {
    pp_node = &(*pp_node)->next;
    --index;
  }
  Node* removed_node = *pp_node;

  // Remove node from list
  *pp_node = removed_node->next;

  // Clean up
  delete removed_node;
}

template <typename DataType>
void LinkedList<DataType>::remove(const DataType& value) {
  Node** pp_node = &head_;

  while (*pp_node) {
    if ((*pp_node)->data == value) {
      Node* removed_node = *pp_node;
      *pp_node = removed_node->next;
      delete removed_node;
      --size_;
      return;
    }

    pp_node = &(*pp_node)->next;
  }
}

template <typename DataType>
DataType LinkedList<DataType>::value_from_back(std::size_t index) {
  std::size_t index_from_front = size_ - index - 1;
  return value_at(index_from_front);
}

template <typename DataType>
void LinkedList<DataType>::reverse() {
  Node* curr_node = head_;
  Node* prev_node = nullptr;
  Node* next_node = nullptr;

  while (curr_node) {
    next_node = curr_node->next;
    curr_node->next = prev_node;
    prev_node = curr_node;
    curr_node = next_node;
  }

  head_ = prev_node;
}

// Private
template <typename DataType>
void LinkedList<DataType>::release_head() {
  while (head_) {
    Node* next_node = head_->next;
    delete head_;
    head_ = next_node;
  }
}

}  // namespace td
