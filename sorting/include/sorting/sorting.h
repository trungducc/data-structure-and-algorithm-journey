#pragma once

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

}  // namespace sorting
}  // namespace td
