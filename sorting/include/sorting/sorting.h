#pragma once

#include <random>
#include <vector>

namespace td {
namespace sorting {

// Private
namespace detail {
// The heap contains first |size| items of given array.
// Swap item at given index with its largest child until its priority is equal
// or greater than both its children.
template <typename ItemType>
void heapify(std::vector<ItemType>& items,
             bool is_max_heap,
             std::size_t size,
             std::size_t index) {
  if (index >= size)
    return;

  std::size_t highest_priority_index = index;
  std::size_t left_child_index = index * 2 + 1;
  std::size_t right_child_index = left_child_index + 1;

  if (left_child_index < size &&
      items[highest_priority_index] < items[left_child_index] == is_max_heap)
    highest_priority_index = left_child_index;
  if (right_child_index < size &&
      items[highest_priority_index] < items[right_child_index] == is_max_heap)
    highest_priority_index = right_child_index;

  if (highest_priority_index == index)
    return;

  std::swap(items[highest_priority_index], items[index]);
  heapify(items, is_max_heap, size, highest_priority_index);
}

// Sort items in given range of array (items[end] is not in the array)
//
// Note: Given range of array must contain 2 sorted sub array.
//       Left sub array is items[begin:middle-1].
//       Right sub array is items[middle:end-1].
template <typename ItemType>
void merge(std::vector<ItemType>& items,
           bool ascending,
           std::size_t begin,
           std::size_t middle,
           std::size_t end) {
  std::vector<ItemType> holder;
  std::size_t l = begin;
  std::size_t r = middle;

  while (l < middle && r < end) {
    if (items[l] < items[r] == ascending)
      holder.push_back(items[l++]);
    else
      holder.push_back(items[r++]);
  }

  while (l < middle)
    holder.push_back(items[l++]);
  while (r < end)
    holder.push_back(items[r++]);

  for (std::size_t i = 0; i < holder.size(); ++i)
    items[i + begin] = holder[i];
}

// Sort items in given range of array (items[end] is not in the array)
template <typename ItemType>
void merge_sort(std::vector<ItemType>& items,
                bool ascending,
                std::size_t begin,
                std::size_t end) {
  if (begin + 2 > end)
    return;

  std::size_t middle = (begin + end) / 2;
  merge_sort(items, ascending, begin, middle);
  merge_sort(items, ascending, middle, end);
  merge(items, ascending, begin, middle, end);
}

// Take first element as pivot, place pivot at its correct position in sorted
// array, and place all smaller (smaller than pivot) to left of pivot and all
// greater elements to right of pivot
template <typename ItemType>
std::size_t partition(std::vector<ItemType>& items,
                      bool ascending,
                      std::size_t begin,
                      std::size_t end) {
  ItemType pivot = items[begin];
  std::size_t l = begin + 1;
  std::size_t r = end - 1;

  while (true) {
    while (l < end && items[l] < pivot == ascending)
      ++l;
    while (r > begin && items[r] > pivot == ascending)
      --r;

    if (l >= r)
      break;
    std::swap(items[l++], items[r--]);
  }

  std::swap(items[r], items[begin]);
  return r;
}

// Sort items in given range of array (items[end] is not in the array)
template <typename ItemType>
void quick_sort(std::vector<ItemType>& items,
                bool ascending,
                std::size_t begin,
                std::size_t end) {
  if (begin + 2 > end)
    return;

  std::size_t pivot_index = partition(items, ascending, begin, end);
  quick_sort(items, ascending, begin, pivot_index);
  quick_sort(items, ascending, pivot_index + 1, end);
}

// Shuffle items in given array
template <typename ItemType>
void shuffle(std::vector<ItemType>& items) {
  auto rng = std::default_random_engine{};
  std::shuffle(std::begin(items), std::end(items), rng);
}

}  // namespace detail

// Bubble sort implementation
template <typename ItemType>
void bubble_sort(std::vector<ItemType>& items, bool ascending = true) {
  for (std::size_t i = 0; i < items.size(); ++i)
    for (std::size_t j = 1; j < items.size() - i; ++j)
      if (ascending == items[j - 1] > items[j])
        std::swap(items[j - 1], items[j]);
}

// Selection sort implementation
template <typename ItemType>
void selection_sort(std::vector<ItemType>& items, bool ascending = true) {
  std::size_t min_index;

  for (std::size_t i = 0; i < items.size(); ++i) {
    min_index = i;

    for (std::size_t j = i; j < items.size(); ++j)
      if (ascending == items[j] < items[min_index])
        min_index = j;
    std::swap(items[i], items[min_index]);
  }
}

// Insertion sort implementation
template <typename ItemType>
void insertion_sort(std::vector<ItemType>& items, bool ascending = true) {
  std::size_t curr_index;
  ItemType inserted_item;

  for (std::size_t i = 1; i < items.size(); ++i) {
    curr_index = i;
    inserted_item = items[i];

    while (curr_index > 0 &&
           ascending == items[curr_index - 1] > inserted_item) {
      items[curr_index] = items[curr_index - 1];
      --curr_index;
    }
    items[curr_index] = inserted_item;
  }
}

// Heap sort implementation
template <typename ItemType>
void heap_sort(std::vector<ItemType>& items, bool ascending = true) {
  std::size_t size = items.size();
  for (int i = size / 2; i >= 0; --i)
    detail::heapify(items, ascending, size, i);

  for (int i = size - 1; i > 0; --i) {
    std::swap(items[0], items[i]);
    detail::heapify(items, ascending, i, 0);
  }
}

// Merge sort implemetation
template <typename ItemType>
void merge_sort(std::vector<ItemType>& items, bool ascending = true) {
  detail::merge_sort(items, ascending, 0, items.size());
}

// Quick sort implemetation
template <typename ItemType>
void quick_sort(std::vector<ItemType>& items, bool ascending = true) {
  detail::shuffle(items);
  detail::quick_sort(items, ascending, 0, items.size());
}

}  // namespace sorting
}  // namespace td
