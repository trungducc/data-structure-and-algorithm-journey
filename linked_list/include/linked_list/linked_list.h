#pragma once

#include <iostream>

#include "utils/utils.h"

namespace td {

template <typename T>
class LinkedList;

template <typename T>
void swap(LinkedList<T>& rhs, LinkedList<T>& lhs);

// A linked list template
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

  // Swap values inside |lhs| and |rhs|.
  // Follow copy-and-swap idiom
  // https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
  friend void swap<T>(LinkedList<T>& lhs, LinkedList<T>& rhs);

 private:
  // Node's data type
  struct Node {
    T data;
    Node* next{nullptr};

    Node(const T& t) : data(t) {}
    Node(const T& t, Node* n) : data(t), next(n) {}
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

template <typename T>
void swap(LinkedList<T>& lhs, LinkedList<T>& rhs) {
  using std::swap;

  swap(lhs.head_, rhs.head_);
  swap(lhs.size_, rhs.size_);
}

// Public
template <typename T>
LinkedList<T>::LinkedList(const T& value) : head_(new Node(value)), size_(1) {}

template <typename T>
LinkedList<T>::LinkedList(std::initializer_list<T> il) {
  for (int i = il.size() - 1; i >= 0; --i) {
    push_front(il.begin()[i]);
  }
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) : size_(other.size_) {
  release_head();

  Node* other_head = other.head_;
  Node** pp_tail = &head_;

  while (other_head) {
    *pp_tail = new Node(other_head->data);
    pp_tail = &(*pp_tail)->next;
    other_head = other_head->next;
  }
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& other)
    : head_(other.head_), size_(other.size_) {
  other.head_ = nullptr;
  other.size_ = 0;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {
  LinkedList<T> temp(other);
  swap(*this, temp);
  return *this;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& other) {
  // Maybe shouldn't use |swap| method for move assignment operator
  // https://stackoverflow.com/questions/6687388/why-do-some-people-use-swap-for-move-assignments
  LinkedList<T> temp = std::move(other);
  swap(*this, temp);
  return *this;
}

template <typename T>
LinkedList<T>::~LinkedList() {
  size_ = 0;
  release_head();
}

template <typename T>
std::size_t LinkedList<T>::size() {
  return size_;
}

template <typename T>
bool LinkedList<T>::is_empty() {
  return size_ == 0;
}

template <typename T>
T LinkedList<T>::value_at(std::size_t index) {
  utils::validate(index, size_, utils::Action::kNone);

  Node* target_node = head_;

  for (std::size_t i = 0; i < index; ++i) {
    target_node = target_node->next;
  }

  return target_node->data;
}

template <typename T>
void LinkedList<T>::push_front(const T& value) {
  ++size_;

  Node* current_head = head_;
  head_ = new Node(value);
  head_->next = current_head;
}

template <typename T>
T LinkedList<T>::pop_front() {
  utils::validate(0, size_, utils::Action::kRemoved);

  Node* removed_node = head_;
  T data = removed_node->data;

  head_ = head_->next;

  delete removed_node;
  --size_;

  return data;
}

template <typename T>
void LinkedList<T>::push_back(const T& value) {
  Node** pp_node = &head_;

  while (*pp_node) {
    pp_node = &(*pp_node)->next;
  }

  *pp_node = new Node(value);
  ++size_;
}

template <typename T>
T LinkedList<T>::pop_back() {
  utils::validate(size_ - 1, size_, utils::Action::kRemoved);

  Node** pp_tail_node = &head_;
  while ((*pp_tail_node)->next) {
    pp_tail_node = &(*pp_tail_node)->next;
  }
  Node* tail_node = *pp_tail_node;
  T data = tail_node->data;

  *pp_tail_node = nullptr;

  delete tail_node;
  --size_;

  return data;
}

template <typename T>
T LinkedList<T>::front() {
  return value_at(0);
}

template <typename T>
T LinkedList<T>::back() {
  return value_at(size_ - 1);
}

template <typename T>
void LinkedList<T>::insert(const T& value, std::size_t index) {
  utils::validate(index, size_, utils::Action::kInserted);

  // Find pointer points to node at given index
  Node** pp_node = &head_;
  while (index > 0) {
    pp_node = &(*pp_node)->next;
    --index;
  }

  // Create new node and make |pp_node| pointer points to it
  Node* new_node = new Node(value, *pp_node);
  *pp_node = new_node;

  ++size_;
}

template <typename T>
void LinkedList<T>::remove_at(std::size_t index) {
  utils::validate(index, size_, utils::Action::kRemoved);

  // Find removed node
  Node** pp_node = &head_;
  while (index > 0) {
    pp_node = &(*pp_node)->next;
    --index;
  }
  Node* removed_node = *pp_node;

  // Remove node from list
  *pp_node = removed_node->next;

  // Free removed node
  delete removed_node;

  --size_;
}

template <typename T>
void LinkedList<T>::remove(const T& value) {
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

template <typename T>
T LinkedList<T>::value_from_back(std::size_t index) {
  std::size_t index_from_front = size_ - index - 1;
  return value_at(index_from_front);
}

template <typename T>
void LinkedList<T>::reverse() {
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
template <typename T>
void LinkedList<T>::release_head() {
  while (head_) {
    Node* next_node = head_->next;
    delete head_;
    head_ = next_node;
  }
}

}  // namespace td
