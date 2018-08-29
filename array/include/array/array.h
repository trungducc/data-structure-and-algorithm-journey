#pragma once

#include <iostream>

namespace td {

constexpr int min_capacity = 16;
// https://stackoverflow.com/questions/1100311/what-is-the-ideal-growth-rate-for-a-dynamically-allocated-array
constexpr int growth_factor = 2;
constexpr int shrink_factor = 4;

constexpr int index_not_found = -1;

template <typename T>
class Array;

template <typename T>
void swap(Array<T>& rhs, Array<T>& lhs);

// A dynamic array template
template <typename T>
class Array {
 public:
  Array();
  Array(std::size_t capacity);
  Array(std::initializer_list<T>&& il);

  Array(const Array<T>& other);
  Array(Array<T>&& other);

  Array<T>& operator=(const Array<T>& other);
  Array<T>& operator=(Array<T>&& other);

  T& operator[](std::size_t index);

  ~Array();

  // Return number of items are currently stored in array.
  std::size_t size();

  // Return number of items it can hold.
  std::size_t capacity();

  // Return array is empty or not.
  bool is_empty();

  // Return items at |index|.
  T item_at(std::size_t index);

  // Append |item| to the end of array.
  void append(const T& item);

  // Insert |item| at |index|.
  void insert(const T& item, std::size_t index);

  // Prepend |item| to the array.
  void prepend(const T& item);

  // Remove last item and return it.
  T pop();

  // Remove item at |index|
  void remove_at(std::size_t index);

  // Look for |item|, remove index holding it.
  void remove(const T& item);

  // Look for |item|, return first index with this
  // value, returns |kIndexNotFound| if not found
  std::size_t find(const T& item);

  // Swap values inside |first| and |second|.
  // Follow copy-and-swap idiom
  // https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
  friend void swap<T>(Array<T>& rhs, Array<T>& lsh);

 private:
  // In case |index| is not a valid index, throw an exception
  // and terminate program. If |inserted| is true, valid range
  // is from 0 to |size_| + 1, otherwise it's from 0 to |size_|
  void throw_out_of_range_error_if_needed(std::size_t index, bool inserted);

  // If |new_size| is equal or greater than |capacity_|, allocate
  // new array with double capacity. If |new_size| is equal or less
  // than |capacity_| / 4, allocate new array with half of capacity.
  void reallocate_if_needed(std::size_t new_size);

  // Deep copy |items_| from |array|
  void deep_copy(const Array<T>& array);

  // Raw array where items are stored.
  T* items_{nullptr};

  // Number of items are currently stored in array.
  std::size_t size_{0};

  // Represent how many total items array can store without reallocation.
  std::size_t capacity_{0};
};

}  // namespace td

/****************  Array implmentation ****************/
namespace td {

template <typename T>
void swap(Array<T>& rhs, Array<T>& lhs) {
  using std::swap;

  swap(rhs.size_, lhs.size_);
  swap(rhs.capacity_, lhs.capacity_);
  swap(rhs.items_, lhs.items_);
}

// Public
template <typename T>
Array<T>::Array() : Array(min_capacity) {}

template <typename T>
Array<T>::Array(std::size_t capacity) : capacity_(capacity) {
  items_ = new T[capacity_];
}

template <typename T>
Array<T>::Array(std::initializer_list<T>&& il) : Array() {
  for (const T& t : il) {
    append(t);
  }
}

template <typename T>
Array<T>::Array(const Array<T>& other) {
  deep_copy(other);
}

template <typename T>
Array<T>::Array(Array<T>&& other)
    : items_(other.items_), size_(other.size_), capacity_(other.capacity_) {
  other.items_ = nullptr;
}

template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& other) {
  Array<T> temp_array(other);
  swap(*this, temp_array);
  return *this;
}

template <typename T>
Array<T>& Array<T>::operator=(Array<T>&& other) {
  // Maybe shouldn't use |swap| method for move assignment operator
  // https://stackoverflow.com/questions/6687388/why-do-some-people-use-swap-for-move-assignments
  Array<T> temp_array = std::move(other);
  swap(*this, temp_array);
  return *this;
}

template <typename T>
T& Array<T>::operator[](std::size_t index) {
  throw_out_of_range_error_if_needed(index, false);
  return items_[index];
}

template <typename T>
Array<T>::~Array() {
  delete[] items_;
}

template <typename T>
std::size_t Array<T>::size() {
  return size_;
}

template <typename T>
std::size_t Array<T>::capacity() {
  return capacity_;
}

template <typename T>
bool Array<T>::is_empty() {
  return size_ == 0;
}

template <typename T>
T Array<T>::item_at(std::size_t index) {
  throw_out_of_range_error_if_needed(index, false);
  return items_[index];
}

template <typename T>
void Array<T>::append(const T& item) {
  reallocate_if_needed(size_ + 1);

  items_[size_++] = item;
}

template <typename T>
void Array<T>::insert(const T& item, std::size_t index) {
  throw_out_of_range_error_if_needed(index, true);
  reallocate_if_needed(size_ + 1);

  for (std::size_t i = size_; i > index; i--) {
    items_[i] = items_[i - 1];
  }

  items_[index] = item;
  size_++;
}

template <typename T>
void Array<T>::prepend(const T& item) {
  insert(item, 0);
}

template <typename T>
T Array<T>::pop() {
  throw_out_of_range_error_if_needed(0, false);

  T& last_item = items_[size_ - 1];

  reallocate_if_needed(--size_);

  return last_item;
}

template <typename T>
void Array<T>::remove_at(std::size_t index) {
  throw_out_of_range_error_if_needed(index, false);

  for (std::size_t i = index; i < size_ - 1; i++) {
    items_[i] = items_[i + 1];
  }

  reallocate_if_needed(--size_);
}

template <typename T>
void Array<T>::remove(const T& item) {
  for (std::size_t i = 0; i < size_; i++) {
    if (items_[i] != item) {
      continue;
    }

    remove_at(i);
    i--;
  }
}

template <typename T>
std::size_t Array<T>::find(const T& item) {
  for (std::size_t i = 0; i < size_; i++) {
    if (item == items_[i]) {
      return i;
    }
  }

  return index_not_found;
}

// Private
template <typename T>
void Array<T>::throw_out_of_range_error_if_needed(std::size_t index, bool inserted) {
  std::size_t size = inserted ? size_ + 1 : size_;
  if (index < size) {
    return;
  }

  throw std::out_of_range("Index " + std::to_string(index) + " out of bounds " +
                          std::to_string(size_) + ".");
}

template <typename T>
void Array<T>::reallocate_if_needed(std::size_t new_size) {
  std::size_t new_capacity = capacity_;

  if (new_size > capacity_) {
    new_capacity *= growth_factor;
  } else if (new_size <= capacity_ / shrink_factor &&
             capacity_ / growth_factor >= min_capacity) {
    new_capacity /= growth_factor;
  } else {
    return;
  }

  T* new_items = new T[new_capacity];

  for (std::size_t i = 0; i < size_; i++) {
    new_items[i] = items_[i];
  }

  delete[] items_;
  items_ = new_items;

  capacity_ = new_capacity;
}

template <typename T>
void Array<T>::deep_copy(const Array<T>& array) {
  size_ = array.size_;
  capacity_ = array.capacity_;

  delete[] items_;

  items_ = new T[capacity_];
  for (std::size_t i = 0; i < size_; i++) {
    items_[i] = array.items_[i];
  }
}

}  // namespace td
