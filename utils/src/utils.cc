#include "utils/utils.h"

#include <iostream>

namespace td {
namespace utils {

void validate(std::size_t index, std::size_t size, Action action) {
  if (size == 0 && action != Action::kInserted) {
    throw std::out_of_range("Access to empty container.");
  }

  std::size_t range = action == Action::kInserted ? size + 1 : size;

  if (index < range) {
    // Valid index
    return;
  }

  throw std::out_of_range("Index " + std::to_string(index) +
                          " is out of bounds [0.." + std::to_string(size) +
                          "].");
}

}  // namespace utils
}  // namespace td

