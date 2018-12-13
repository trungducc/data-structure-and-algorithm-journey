#pragma once

#include <vector>

namespace td {
namespace sorting {

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

}  // namespace sorting
}  // namespace td