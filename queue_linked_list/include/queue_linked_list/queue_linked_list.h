#pragma once

#include <iostream>

#include "utils/utils.h"

namespace td {

// Implemented queue by using linked list
template <typename T>
class Queue {
 public:
  Queue() = default;
  ~Queue();

  // Determine queue is empty or not.
  bool is_empty();

  // Add given value to queue
  void enqueue(const T& value);

  // Remove least recently-added item from queue and return its value.
  T dequeue();

 private:
  // Node's data type
  struct Node {
    T data;
    Node* next{nullptr};
    Node* prev{nullptr};

    Node() {}
    Node(const T& t) : data(t) {}
  };

  // The node which has |next| is the least recently-added element and 
  // |prev| is the most recently-added element
  Node* sentinel_{new Node()};

  DISALLOW_COPY_AND_ASSIGN(Queue);
};
}  // namespace td

/****************  Queue implementation ****************/
namespace td {

template <typename T>
Queue<T>::~Queue<T>() {
  while (sentinel_) {
    Node* next_node = sentinel_->next;
    delete sentinel_;
    sentinel_ = next_node;
  }
}

template <typename T>
bool Queue<T>::is_empty() {
  return sentinel_->next == nullptr;
}

template <typename T>
void Queue<T>::enqueue(const T& value) {
  Node* new_node = new Node(value);

  if (is_empty()) {
    sentinel_->next = new_node;
    sentinel_->prev = new_node;
    return;
  }

  sentinel_->prev->next = new_node;
  new_node->prev = sentinel_->prev;
  sentinel_->prev = new_node;
}

template <typename T>
T Queue<T>::dequeue() {
  if (is_empty()) {
    utils::validate(0, 0, utils::Action::kRemoved);
  }

  Node* dequeued_node = sentinel_->next;

  if (sentinel_->next == sentinel_->prev) {
    sentinel_->prev = nullptr; 
  }
  sentinel_->next = sentinel_->next->next;

  T data = dequeued_node->data;
  delete dequeued_node;

  return data;
}

}  // namespacetd
