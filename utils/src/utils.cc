#include "utils/utils.h"

#include <math.h>
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

bool is_prime(unsigned long long number) {
  if (number < 2) return false;
  if (number == 2) return true;
  if (number % 2 == 0) return false;
  for (unsigned long long i = 3; i <= sqrt(number); i += 2) {
    if (number % i == 0)
      return false;
  }
  return true;
}

unsigned long long next_prime(unsigned long long number) {
  if (number <= 2) return 2;
  number = number % 2 == 0 ? number + 1 : number;
  while (!is_prime(number))
    number += 2;
  return number;
}

}  // namespace utils
}  // namespace td

