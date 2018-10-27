#pragma once

#include <iostream>

#include "utils/macros.h"
#include "utils/utils.h"

namespace td {

// Implemented queue by using linked list
template <typename DataType>
class Queue {
 public:
  Queue() = default;
  ~Queue();

  // Determine queue is empty or not.
  bool is_empty();

  // Add given value to queue
  void enqueue(const DataType& value);

  // Remove least recently-added item from queue and return its value.
  DataType dequeue();

 private:
  // Node's data type
  struct Node {
    DataType data;
    Node* next{nullptr};
    Node* prev{nullptr};

    Node() {}
    Node(const DataType& t) : data(t) {}
  };

  // The node which has |next| is the least recently-added element and 
  // |prev| is the most recently-added element
  Node* sentinel_{new Node()};

  DISALLOW_COPY_AND_ASSIGN(Queue);
};

}  // namespace td

/****************  Queue implementation ****************/
namespace td {

template <typename DataType>
Queue<DataType>::~Queue<DataType>() {
  while (sentinel_) {
    Node* next_node = sentinel_->next;
    delete sentinel_;
    sentinel_ = next_node;
  }
}

template <typename DataType>
bool Queue<DataType>::is_empty() {
  return sentinel_->next == nullptr;
}

template <typename DataType>
void Queue<DataType>::enqueue(const DataType& value) {
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

template <typename DataType>
DataType Queue<DataType>::dequeue() {
  if (is_empty()) {
    utils::validate(0, 0, utils::Action::kRemoved);
  }

  Node* dequeued_node = sentinel_->next;

  if (sentinel_->next == sentinel_->prev) {
    sentinel_->prev = nullptr; 
  }
  sentinel_->next = sentinel_->next->next;

  DataType data = dequeued_node->data;
  delete dequeued_node;

  return data;
}

}  // namespace td
