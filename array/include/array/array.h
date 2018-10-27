#pragma once

#include <iostream>

#include "utils/utils.h"

namespace td {

constexpr int min_capacity = 16;
// https://stackoverflow.com/questions/1100311/what-is-the-ideal-growth-rate-for-a-dynamically-allocated-array
constexpr int growth_factor = 2;
constexpr int shrink_factor = 4;

constexpr int index_not_found = -1;

template <typename DataType>
class Array;

template <typename DataType>
void swap(Array<DataType>& lhs, Array<DataType>& rhs);

// A dynamic array template
template <typename DataType>
class Array {
 public:
  Array();
  Array(std::size_t capacity);
  Array(std::initializer_list<DataType>&& il);

  Array(const Array<DataType>& other);
  Array(Array<DataType>&& other);

  Array<DataType>& operator=(const Array<DataType>& other);
  Array<DataType>& operator=(Array<DataType>&& other);

  DataType& operator[](std::size_t index);

  ~Array();

  // Return number of items are currently stored in array.
  std::size_t size();

  // Return number of items array can hold.
  std::size_t capacity();

  // Return array is empty or not.
  bool is_empty();

  // Return item at |index|.
  DataType item_at(std::size_t index);

  // Append |item| to the end of array.
  void append(const DataType& item);

  // Insert |item| at |index|.
  void insert(const DataType& item, std::size_t index);

  // Prepend |item| to the array.
  void prepend(const DataType& item);

  // Remove last item and return it.
  DataType pop();

  // Remove item at |index|
  void remove_at(std::size_t index);

  // Look for |item|, remove indexs holding it.
  void remove(const DataType& item);

  // Look for |item|, return first index with this
  // value, returns |kIndexNotFound| if not found
  std::size_t find(const DataType& item);

  // Swap values inside |lhs| and |rhs|.
  // Follow copy-and-swap idiom
  // https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
  friend void swap<DataType>(Array<DataType>& lhs, Array<DataType>& rhs);

 private:
  // If |new_size| is equal or greater than |capacity_|, allocate
  // new array with double capacity. If |new_size| is equal or less
  // than |capacity_| / 4, allocate new array with half of capacity.
  void reallocate_if_needed(std::size_t new_size);

  // Deep copy |items_| from |array|
  void deep_copy(const Array<DataType>& array);

  // Raw array where items are stored.
  DataType* items_{nullptr};

  // Number of items are currently stored in array.
  std::size_t size_{0};

  // Represent how many total items array can store without reallocation.
  std::size_t capacity_{0};
};

}  // namespace td

/****************  Array implementation ****************/
namespace td {

template <typename DataType>
void swap(Array<DataType>& lhs, Array<DataType>& rhs) {
  using std::swap;

  swap(lhs.size_, rhs.size_);
  swap(lhs.capacity_, rhs.capacity_);
  swap(lhs.items_, rhs.items_);
}

// Public
template <typename DataType>
Array<DataType>::Array() : Array(min_capacity) {}

template <typename DataType>
Array<DataType>::Array(std::size_t capacity) : capacity_(capacity) {
  items_ = new DataType[capacity_];
}

template <typename DataType>
Array<DataType>::Array(std::initializer_list<DataType>&& il) : Array() {
  for (const DataType& t : il) {
    append(t);
  }
}

template <typename DataType>
Array<DataType>::Array(const Array<DataType>& other) {
  deep_copy(other);
}

template <typename DataType>
Array<DataType>::Array(Array<DataType>&& other)
    : items_(other.items_), size_(other.size_), capacity_(other.capacity_) {
  other.items_ = nullptr;
}

template <typename DataType>
Array<DataType>& Array<DataType>::operator=(const Array<DataType>& other) {
  Array<DataType> temp_array(other);
  swap(*this, temp_array);
  return *this;
}

template <typename DataType>
Array<DataType>& Array<DataType>::operator=(Array<DataType>&& other) {
  // Maybe shouldn't use |swap| method for move assignment operator
  // https://stackoverflow.com/questions/6687388/why-do-some-people-use-swap-for-move-assignments
  Array<DataType> temp_array = std::move(other);
  swap(*this, temp_array);
  return *this;
}

template <typename DataType>
DataType& Array<DataType>::operator[](std::size_t index) {
  utils::validate(index, size_, utils::Action::kNone);
  return items_[index];
}

template <typename DataType>
Array<DataType>::~Array() {
  delete[] items_;
}

template <typename DataType>
std::size_t Array<DataType>::size() {
  return size_;
}

template <typename DataType>
std::size_t Array<DataType>::capacity() {
  return capacity_;
}

template <typename DataType>
bool Array<DataType>::is_empty() {
  return size_ == 0;
}

template <typename DataType>
DataType Array<DataType>::item_at(std::size_t index) {
  utils::validate(index, size_, utils::Action::kNone);
  return items_[index];
}

template <typename DataType>
void Array<DataType>::append(const DataType& item) {
  reallocate_if_needed(size_ + 1);
  items_[size_++] = item;
}

template <typename DataType>
void Array<DataType>::insert(const DataType& item, std::size_t index) {
  utils::validate(index, size_, utils::Action::kInserted);
  reallocate_if_needed(++size_);

  for (std::size_t i = size_ - 1; i > index; --i) {
    items_[i] = items_[i - 1];
  }

  items_[index] = item;
}

template <typename DataType>
void Array<DataType>::prepend(const DataType& item) {
  insert(item, 0);
}

template <typename DataType>
DataType Array<DataType>::pop() {
  std::size_t last_index = size_ - 1;
  utils::validate(last_index, size_, utils::Action::kRemoved);

  DataType& last_item = items_[last_index];

  reallocate_if_needed(--size_);
  return last_item;
}

template <typename DataType>
void Array<DataType>::remove_at(std::size_t index) {
  utils::validate(index, size_, utils::Action::kRemoved);

  for (std::size_t i = index; i < size_ - 1; ++i) {
    items_[i] = items_[i + 1];
  }

  reallocate_if_needed(--size_);
}

template <typename DataType>
void Array<DataType>::remove(const DataType& item) {
  for (std::size_t i = 0; i < size_; ++i) {
    if (items_[i] != item) {
      continue;
    }

    remove_at(i--);
  }
}

template <typename DataType>
std::size_t Array<DataType>::find(const DataType& item) {
  for (std::size_t i = 0; i < size_; ++i) {
    if (item == items_[i]) {
      return i;
    }
  }

  return index_not_found;
}

template <typename DataType>
void Array<DataType>::reallocate_if_needed(std::size_t new_size) {
  std::size_t new_capacity = capacity_;

  if (new_size > capacity_) {
    new_capacity *= growth_factor;
  } else if (new_size <= capacity_ / shrink_factor &&
             capacity_ / growth_factor >= min_capacity) {
    new_capacity /= growth_factor;
  } else {
    return;
  }

  DataType* new_items = new DataType[new_capacity];

  for (std::size_t i = 0; i < size_; ++i) {
    new_items[i] = items_[i];
  }

  delete[] items_;
  items_ = new_items;

  capacity_ = new_capacity;
}

template <typename DataType>
void Array<DataType>::deep_copy(const Array<DataType>& array) {
  size_ = array.size_;
  capacity_ = array.capacity_;

  delete[] items_;

  items_ = new DataType[capacity_];
  for (std::size_t i = 0; i < size_; ++i) {
    items_[i] = array.items_[i];
  }
}

}  // namespace td
