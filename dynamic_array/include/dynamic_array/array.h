#ifndef CPP_DYNAMIC_ARRAY_H_
#define CPP_DYNAMIC_ARRAY_H_

#include <iostream>

namespace td {

static const int kMinCapacity = 16;
// https://stackoverflow.com/questions/1100311/what-is-the-ideal-growth-rate-for-a-dynamically-allocated-array
static const int kGrowthFactor = 2;
static const int kShrinkFactor = 4;

static const int kIndexNotFound = -1;

template <typename T>
class Array;

template <typename T>
void swap(Array<T>& rhs, Array<T>& lhs);

// A dynamic array template
template <typename T>
class Array {
 public:
  Array();
  Array(size_t capacity);
  Array(std::initializer_list<T> il);

  Array(const Array<T>& array);
  Array(Array<T>&& array);

  Array<T>& operator=(const Array<T>& array);
  Array<T>& operator=(Array<T>&& array);

  ~Array();

  // Return number of items are currently stored in array.
  size_t GetSize();

  // Return number of items it can hold.
  size_t GetCapacity();

  // Return array is empty or not.
  bool IsEmpty();

  // Return items at |index|.
  T GetItemAt(int index);

  // Append |item| to the end of array.
  void Append(const T& item);

  // Insert |item| at |index|.
  void Insert(const T& item, int index);

  // Prepend |item| to the array.
  void Prepend(const T& item);

  // Remove last item and return it.
  T Pop();

  // Delete item at |index|
  void Delete(int index);

  // Look for |item|, remove index holding it.
  void Remove(const T& item);

  // Look for |item|, return first index with this
  // value, returns |kIndexNotFound| if not found
  int Find(const T& item);

  // Swap values inside |first| and |second|.
  // Follow copy-and-swap idiom
  // https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
  friend void swap<T>(Array<T>& rhs, Array<T>& lsh);

 private:
  // If |index| is a negative value or greater than
  // |size_|, log an error and terminate program.
  void ThrowIndexOutOfBoundsErrorIfNeeded(int index);

  // If |new_size| is equal or greater than |capacity_|, allocate
  // new array with double capacity. If |new_size| is equal or less
  // than |capacity_| / 4, allocate new array with half of capacity.
  void ReallocateIfNeeded(size_t new_size);

  // Deep copy |items_| from |array|
  void DeepCopy(const Array<T>& array);

  // Raw array where items are stored.
  T* items_{nullptr};

  // Number of items are currently stored in array.
  size_t size_{0};

  // Represent how many total items array can store without reallocation.
  size_t capacity_{0};
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
Array<T>::Array() : Array(kMinCapacity) {}

template <typename T>
Array<T>::Array(size_t capacity) : capacity_(capacity) {
  items_ = new T[capacity_];
}

template <typename T>
Array<T>::Array(std::initializer_list<T> il) : Array() {
  for (const T& t : il) {
    Append(t);
  }
}

template <typename T>
Array<T>::Array(const Array<T>& array) {
  DeepCopy(array);
}

template <typename T>
Array<T>::Array(Array<T>&& array)
    : items_(array.items_), size_(array.size_), capacity_(array.capacity_) {
  array.items_ = nullptr;
}

template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& array) {
  Array<T> temp_array(array);
  swap(*this, temp_array);
  return *this;
}

template <typename T>
Array<T>& Array<T>::operator=(Array<T>&& array) {
  // Maybe shouldn't use |swap| method for move assignment operator
  // https://stackoverflow.com/questions/6687388/why-do-some-people-use-swap-for-move-assignments
  Array<T> temp_array = std::move(array);
  swap(*this, temp_array);
  return *this;
}

template <typename T>
Array<T>::~Array() {
  delete[] items_;
}

template <typename T>
size_t Array<T>::GetSize() {
  return size_;
}

template <typename T>
size_t Array<T>::GetCapacity() {
  return capacity_;
}

template <typename T>
bool Array<T>::IsEmpty() {
  return size_ == 0;
}

template <typename T>
T Array<T>::GetItemAt(int index) {
  ThrowIndexOutOfBoundsErrorIfNeeded(index);

  return items_[index];
}

template <typename T>
void Array<T>::Append(const T& item) {
  ReallocateIfNeeded(size_ + 1);

  items_[size_] = item;
  size_++;
}

template <typename T>
void Array<T>::Insert(const T& item, int index) {
  ThrowIndexOutOfBoundsErrorIfNeeded(index);
  ReallocateIfNeeded(size_ + 1);

  for (size_t i = size_; i > index; i--) {
    items_[i] = items_[i - 1];
  }

  items_[index] = item;
  size_++;
}

template <typename T>
void Array<T>::Prepend(const T& item) {
  Insert(item, 0);
}

template <typename T>
T Array<T>::Pop() {
  ThrowIndexOutOfBoundsErrorIfNeeded(0);

  T& last_item = items_[size_ - 1];

  ReallocateIfNeeded(--size_);

  return last_item;
}

template <typename T>
void Array<T>::Delete(int index) {
  ThrowIndexOutOfBoundsErrorIfNeeded(index);

  for (size_t i = index; i < size_ - 1; i++) {
    items_[i] = items_[i + 1];
  }

  ReallocateIfNeeded(--size_);
}

template <typename T>
void Array<T>::Remove(const T& item) {
  for (size_t i = 0; i < size_; i++) {
    if (items_[i] != item) {
      continue;
    }

    Delete(i);
    i--;
  }
}

template <typename T>
int Array<T>::Find(const T& item) {
  for (size_t i = 0; i < size_; i++) {
    if (item == items_[i]) {
      return i;
    }
  }

  return kIndexNotFound;
}

// Private
template <typename T>
void Array<T>::ThrowIndexOutOfBoundsErrorIfNeeded(int index) {
  if (!IsEmpty() && index >= 0 && index < size_) {
    return;
  }

  throw std::out_of_range("Index " + std::to_string(index) + " out of bounds " +
                          std::to_string(size_) + ".");
}

template <typename T>
void Array<T>::ReallocateIfNeeded(size_t new_size) {
  size_t new_capacity = capacity_;

  if (new_size > capacity_) {
    new_capacity *= kGrowthFactor;
  } else if (new_size <= capacity_ / kShrinkFactor &&
             capacity_ / kGrowthFactor >= kMinCapacity) {
    new_capacity /= kGrowthFactor;
  } else {
    return;
  }

  T* new_items = new T[new_capacity];

  for (size_t i = 0; i < size_; i++) {
    new_items[i] = items_[i];
  }

  delete[] items_;
  items_ = new_items;

  capacity_ = new_capacity;
}

template <typename T>
void Array<T>::DeepCopy(const Array<T>& array) {
  size_ = array.size_;
  capacity_ = array.capacity_;

  delete[] items_;

  items_ = new T[capacity_];
  for (size_t i = 0; i < size_; i++) {
    items_[i] = array.items_[i];
  }
}

}  // namespace td

#endif  // CPP_DYNAMIC_ARRAY_H_
