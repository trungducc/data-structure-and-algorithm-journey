#pragma once

#include <vector>

namespace td {
namespace sorting {

// Bubble sort implementation
template <typename ItemType>
void bubble_sort(std::vector<ItemType>& items, bool ascending = true) {
  for (int i = 0; i < items.size(); ++i)
    for (int j = 1; j < items.size() - i; ++j)
      if (ascending == items[j - 1] > items[j])
        std::swap(items[j - 1], items[j]);
}

}  // namespace sorting
}  // namespace td