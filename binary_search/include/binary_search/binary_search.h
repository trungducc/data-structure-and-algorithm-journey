#pragma once

#include <vector>

namespace td {

// Returns either the index of the location in the vector, or -1 if the vector
// doesn't contain the target.
template <typename DataType>
std::size_t binary_search(const std::vector<DataType>& vector,
                          const DataType& target);

// Binary search implementation using recursion.
template <typename DataType>
std::size_t recursion_binary_search(const std::vector<DataType>& vector,
                                    const DataType& target,
                                    std::size_t lower_bound,
                                    std::size_t upper_bound);

}  // namespace td

/****************  Binary search implementation ****************/
namespace td {

template <typename DataType>
std::size_t binary_search(const std::vector<DataType>& vector,
                          const DataType& target) {
  long long lower_bound = 0;
  long long upper_bound = vector.size() - 1;
  long long mid_point;

  while (lower_bound <= upper_bound) {
    mid_point = (lower_bound + upper_bound) / 2;

    if (vector[mid_point] == target) {
      return mid_point;
    } else if (vector[mid_point] > target) {
      upper_bound = mid_point - 1;
    } else {
      lower_bound = mid_point + 1;
    }
  }

  return -1;
}

template <typename DataType>
std::size_t recursion_binary_search(const std::vector<DataType>& vector,
                                    const DataType& target,
                                    std::size_t lower_bound,
                                    std::size_t upper_bound) {
  if (lower_bound > vector.size() - 1 || upper_bound > vector.size() - 1 ||
      lower_bound < 0 || upper_bound < 0 || lower_bound > upper_bound)
    return -1;

  long long mid_point = (lower_bound + upper_bound) / 2;

  if (vector[mid_point] == target) {
    return mid_point;
  } else if (vector[mid_point] > target) {
    upper_bound = mid_point - 1;
  } else {
    lower_bound = mid_point + 1;
  }

  return recursion_binary_search(vector, target, lower_bound, upper_bound);
}

}  // namespace td
