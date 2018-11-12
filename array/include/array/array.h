#pragma once

#include "utils/utils.h"

namespace td {

constexpr int min_capacity = 16;
// https://stackoverflow.com/questions/1100311/what-is-the-ideal-growth-rate-for-a-dynamically-allocated-array
constexpr int growth_factor = 2;
constexpr int shrink_factor = 4;

constexpr int index_not_found = -1;

template <typename ItemType>
class Array;

template <typename ItemType>
void swap(Array<ItemType>& lhs, Array<ItemType>& rhs);

// A dynamic array template
template <typename ItemType>
class Array {
 public:
  Array();
  Array(std::size_t capacity);
  Array(std::initializer_list<ItemType>&& il);

  Array(const Array<ItemType>& other);
  Array(Array<ItemType>&& other);

  Array<ItemType>& operator=(const Array<ItemType>& other);
  Array<ItemType>& operator=(Array<ItemType>&& other);

  ItemType& operator[](std::size_t index);

  ~Array();

  // Return number of items are currently stored in array.
  std::size_t size();

  // Return number of items array can hold.
  std::size_t capacity();

  // Return array is empty or not.
  bool is_empty();

  // Return item at |index|.
  ItemType item_at(std::size_t index);

  // Append |item| to the end of array.
  void append(const ItemType& item);

  // Insert |item| at |index|.
  void insert(const ItemType& item, std::size_t index);

  // Prepend |item| to the array.
  void prepend(const ItemType& item);

  // Remove last item and return it.
  ItemType pop();

  // Remove item at |index|
  void remove_at(std::size_t index);

  // Look for |item|, remove indexs holding it.
  void remove(const ItemType& item);

  // Look for |item|, return first index with this
  // value, returns |kIndexNotFound| if not found
  std::size_t find(const ItemType& item);

  // Swap values inside |lhs| and |rhs|.
  // Follow copy-and-swap idiom
  // https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
  friend void swap<ItemType>(Array<ItemType>& lhs, Array<ItemType>& rhs);

 private:
  // If |new_size| is equal or greater than |capacity_|, allocate
  // new array with double capacity. If |new_size| is equal or less
  // than |capacity_| / 4, allocate new array with half of capacity.
  void reallocate_if_needed(std::size_t new_size);

  // Deep copy |items_| from |array|
  void deep_copy(const Array<ItemType>& array);

  // Raw array where items are stored.
  ItemType* items_{nullptr};

  // Number of items are currently stored in array.
  std::size_t size_{0};

  // Represent how many total items array can store without reallocation.
  std::size_t capacity_{0};
};

}  // namespace td

/****************  Array implementation ****************/
namespace td {

template <typename ItemType>
void swap(Array<ItemType>& lhs, Array<ItemType>& rhs) {
  using std::swap;

  swap(lhs.size_, rhs.size_);
  swap(lhs.capacity_, rhs.capacity_);
  swap(lhs.items_, rhs.items_);
}

// Public
template <typename ItemType>
Array<ItemType>::Array() : Array(min_capacity) {}

template <typename ItemType>
Array<ItemType>::Array(std::size_t capacity) : capacity_(capacity) {
  items_ = new ItemType[capacity_];
}

template <typename ItemType>
Array<ItemType>::Array(std::initializer_list<ItemType>&& il) : Array() {
  for (const ItemType& data : il) {
    append(data);
  }
}

template <typename ItemType>
Array<ItemType>::Array(const Array<ItemType>& other) {
  deep_copy(other);
}

template <typename ItemType>
Array<ItemType>::Array(Array<ItemType>&& other)
    : items_(other.items_), size_(other.size_), capacity_(other.capacity_) {
  other.items_ = nullptr;
}

template <typename ItemType>
Array<ItemType>& Array<ItemType>::operator=(const Array<ItemType>& other) {
  Array<ItemType> temp_array(other);
  swap(*this, temp_array);
  return *this;
}

template <typename ItemType>
Array<ItemType>& Array<ItemType>::operator=(Array<ItemType>&& other) {
  // Maybe shouldn't use |swap| method for move assignment operator
  // https://stackoverflow.com/questions/6687388/why-do-some-people-use-swap-for-move-assignments
  Array<ItemType> temp_array = std::move(other);
  swap(*this, temp_array);
  return *this;
}

template <typename ItemType>
ItemType& Array<ItemType>::operator[](std::size_t index) {
  utils::validate(index, size_, utils::Action::kNone);
  return items_[index];
}

template <typename ItemType>
Array<ItemType>::~Array() {
  delete[] items_;
}

template <typename ItemType>
std::size_t Array<ItemType>::size() {
  return size_;
}

template <typename ItemType>
std::size_t Array<ItemType>::capacity() {
  return capacity_;
}

template <typename ItemType>
bool Array<ItemType>::is_empty() {
  return size_ == 0;
}

template <typename ItemType>
ItemType Array<ItemType>::item_at(std::size_t index) {
  utils::validate(index, size_, utils::Action::kNone);
  return items_[index];
}

template <typename ItemType>
void Array<ItemType>::append(const ItemType& item) {
  reallocate_if_needed(size_ + 1);
  items_[size_++] = item;
}

template <typename ItemType>
void Array<ItemType>::insert(const ItemType& item, std::size_t index) {
  utils::validate(index, size_, utils::Action::kInsert);
  reallocate_if_needed(++size_);

  for (std::size_t i = size_ - 1; i > index; --i) {
    items_[i] = items_[i - 1];
  }

  items_[index] = item;
}

template <typename ItemType>
void Array<ItemType>::prepend(const ItemType& item) {
  insert(item, 0);
}

template <typename ItemType>
ItemType Array<ItemType>::pop() {
  std::size_t last_index = size_ - 1;
  utils::validate(last_index, size_, utils::Action::kRemove);

  ItemType& last_item = items_[last_index];

  reallocate_if_needed(--size_);
  return last_item;
}

template <typename ItemType>
void Array<ItemType>::remove_at(std::size_t index) {
  utils::validate(index, size_, utils::Action::kRemove);

  for (std::size_t i = index; i < size_ - 1; ++i) {
    items_[i] = items_[i + 1];
  }

  reallocate_if_needed(--size_);
}

template <typename ItemType>
void Array<ItemType>::remove(const ItemType& item) {
  for (std::size_t i = 0; i < size_; ++i) {
    if (items_[i] != item) {
      continue;
    }

    remove_at(i--);
  }
}

template <typename ItemType>
std::size_t Array<ItemType>::find(const ItemType& item) {
  for (std::size_t i = 0; i < size_; ++i) {
    if (item == items_[i]) {
      return i;
    }
  }

  return index_not_found;
}

template <typename ItemType>
void Array<ItemType>::reallocate_if_needed(std::size_t new_size) {
  std::size_t new_capacity = capacity_;

  if (new_size > capacity_) {
    new_capacity *= growth_factor;
  } else if (new_size <= capacity_ / shrink_factor &&
             capacity_ / growth_factor >= min_capacity) {
    new_capacity /= growth_factor;
  } else {
    return;
  }

  ItemType* new_items = new ItemType[new_capacity];

  for (std::size_t i = 0; i < size_; ++i) {
    new_items[i] = items_[i];
  }

  delete[] items_;
  items_ = new_items;

  capacity_ = new_capacity;
}

template <typename ItemType>
void Array<ItemType>::deep_copy(const Array<ItemType>& array) {
  size_ = array.size_;
  capacity_ = array.capacity_;

  delete[] items_;

  items_ = new ItemType[capacity_];
  for (std::size_t i = 0; i < size_; ++i) {
    items_[i] = array.items_[i];
  }
}

}  // namespace td
