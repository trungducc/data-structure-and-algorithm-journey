#pragma once

#include <iostream>

#include "utils/macros.h"
#include "utils/utils.h"

namespace td {

constexpr std::size_t default_capacity = 16;

// Implemented queue by using array
template <typename DataType>
class Queue {
 public:
  Queue();
  Queue(std::size_t capacity);

  ~Queue();

  // Determine queue is empty or not.
  bool is_empty();

  // Determine number of items in queue is reached capacity or not.
  bool is_full();

  // Add given value to queue. If queue is full, do nothing.
  void enqueue(const DataType& value);

  // Remove least recently-added item from queue and return its value.
  DataType dequeue();

 private:
  // Raw array where items are stored.
  DataType* items_{nullptr};

  // Calling |enqueue| will insert an item to this index.
  std::size_t enqueue_index_{0};

  // Index of item which will be returned when calling |dequeue|.
  std::size_t dequeue_index_{0};

  // Represent how many total items queue can store.
  std::size_t capacity_{0};

  DISALLOW_COPY_AND_ASSIGN(Queue);
};

}  // namespace td

/****************  Queue implementation ****************/
namespace td {

template <typename DataType>
Queue<DataType>::Queue() : Queue(default_capacity) {}

template <typename DataType>
Queue<DataType>::Queue(std::size_t capacity)
    : items_(new DataType[++capacity]), capacity_(capacity) {}

template <typename DataType>
Queue<DataType>::~Queue() {
  delete[] items_;
}

template <typename DataType>
bool Queue<DataType>::is_empty() {
  return enqueue_index_ == dequeue_index_;
}

template <typename DataType>
bool Queue<DataType>::is_full() {
  return (enqueue_index_ + 1) % capacity_ == dequeue_index_;
}

template <typename DataType>
void Queue<DataType>::enqueue(const DataType& value) {
  if (is_full()) {
    return;
  }

  items_[enqueue_index_] = value;

  if (enqueue_index_ == capacity_ - 1) {
    enqueue_index_ = 0;
  } else {
    ++enqueue_index_;
  }
}

template <typename DataType>
DataType Queue<DataType>::dequeue() {
  if (is_empty()) {
    utils::validate(0, 0, utils::Action::kRemove);
  }

  DataType data = items_[dequeue_index_];
  items_[dequeue_index_] = 0;

  if (dequeue_index_ == capacity_ - 1) {
    dequeue_index_ = 0;
  } else {
    ++dequeue_index_;
  }

  return data;
}

}  // namespace td
