#pragma once

#include <limits>
#include <stdexcept>

#include "utils/macros.h"
#include "utils/utils.h"

namespace td {

// Priority Queue implementation by using max heap.
template <typename DataType>
class PriorityQueue {
 public:
  using Priority = int;

  PriorityQueue(std::size_t capacity);

  ~PriorityQueue();

  // Return true if there is no item in priority queue. Otherwise, return false.
  bool is_empty();

  // Return number of items stored in priority queue.
  std::size_t size();

  // Return data of item which has greatest priority.
  DataType max();

  // Remove item which has greatest priority and return its data.
  DataType extract_max();

  // If |data| exists in priority queue, update its item with given priority.
  // Otherwise, does nothing.
  void update(const DataType& data, const Priority& new_priority);

  // Insert new item. If priority queue is full, does nothing.
  void insert(const DataType& data, const Priority& priority);

  // Remove given data from priority queue.
  void remove(const DataType& data);

 private:
  // Represent an element of priority queue.
  struct Item {
    DataType data;
    Priority priority;

    Item(const DataType& d, const Priority& p);
  };

  // Swaps item at given with its parent until it's not greater than its parent.
  void sift_up(std::size_t index);

  // Swaps item at given with its largest child until it's equal or greater than
  // both its children.
  void sift_down(std::size_t index);

  // Swap items at 2 given indexes.
  void swap(std::size_t first, std::size_t second);

  // Remove item at given index.
  void remove_at(std::size_t index);

  // Return index of item which keeps given data. If it doesn't exist, return
  // |index_not_found|.
  std::size_t index_of(const DataType& data);

  // Number of items are currently stored in priority queue.
  std::size_t size_;

  // Represent how many total items priority queue can store.
  std::size_t capacity_;

  // Raw array where items are stored.
  Item* items_;

  DISALLOW_COPY_AND_ASSIGN(PriorityQueue);
};

}  // namespace td

/****************  PriorityQueue implementation ****************/
namespace td {

// Public
template <typename DataType>
PriorityQueue<DataType>::PriorityQueue(std::size_t capacity)
    : size_(0), capacity_(capacity), items_(new Item[capacity]) {}

template <typename DataType>
PriorityQueue<DataType>::~PriorityQueue() {
  delete[] items_;
}

template <typename DataType>
bool PriorityQueue<DataType>::is_empty() {
  return size_ == 0;
}

template <typename DataType>
DataType PriorityQueue<DataType>::max() {
  if (size_ == 0) {
    throw std::out_of_range("Cannot call |max| on empty priority queue.");
  }
  return items_[0].data;
}

template <typename DataType>
DataType PriorityQueue<DataType>::extract_max() {
  if (size_ == 0) {
    throw std::out_of_range(
        "Cannot call |extract_max| on empty priority queue.");
  }

  DataType max = max();

  items_[0] = items_[--size_];
  items_[size_] = 0;
  sift_down(0);

  return max;
}

template <typename DataType>
void PriorityQueue<DataType>::update(const DataType& data,
                                     const Priority& new_priority) {
  std::size_t updated_index = index_of(data);
  if (updated_index == index_not_found)
    return;

  Priority old_priority = items_[updated_index].priority;
  items_[updated_index].priority = new_priority;

  if (old_priority > new_priority) {
    sift_down(updated_index);
  } else {
    sift_up(updated_index);
  }
}

template <typename DataType>
void PriorityQueue<DataType>::insert(const DataType& data,
                                     const Priority& priority) {
  if (size_ == capacity_)
    return;
  items_[size_] = Item(data, priority);
  sift_up(size_++);
}

template <typename DataType>
void PriorityQueue<DataType>::remove(const DataType& data) {
  std::size_t removed_index = index_of(data);
  if (removed_index != index_not_found)
    remove_at(removed_index);
}

// Private
template <typename DataType>
PriorityQueue<DataType>::Item::Item(const DataType& d, const Priority& p)
    : data(d), priority(p) {}

template <typename DataType>
void PriorityQueue<DataType>::sift_up(std::size_t index) {
  if (index == 0 || index >= size_)
    return;

  std::size_t parent_index = index / 2;

  if (items_[index].priority <= items_[parent_index].priority)
    return;

  swap(index, parent_index);
  sift_up(parent_index);
}

template <typename DataType>
void PriorityQueue<DataType>::sift_down(std::size_t index) {
  if (index >= size_)
    return;

  std::size_t highest_priority_index = index;
  std::size_t left_child_index = index * 2;
  std::size_t right_child_index = left_child_index + 1;

  if (left_child_index < size_ &&
      items_[highest_priority_index].priority <
          items_[left_child_index].priority)
    highest_priority_index = left_child_index;
  if (right_child_index < size_ &&
      items_[highest_priority_index].priority <
          items_[right_child_index].priority)
    highest_priority_index = right_child_index;

  if (index == highest_priority_index)
    return;

  swap(index, highest_priority_index);
  sift_down(highest_priority_index);
}

template <typename DataType>
void PriorityQueue<DataType>::swap(std::size_t first, std::size_t second) {
  Item temp = items_[first];
  items_[first] = items_[second];
  items_[second] = temp;
}

template <typename DataType>
void PriorityQueue<DataType>::remove_at(std::size_t index) {
  items_[index].priority = std::numeric_limits<int>::max();
  sift_up(index);
  extract_max();
}

template <typename DataType>
std::size_t PriorityQueue<DataType>::index_of(const DataType& data) {
  for (std::size_t i = 0; i < size_; ++i) {
    if (data == items_[i].data)
      return i;
  }
  return index_not_found;
}

}  // namespace td
