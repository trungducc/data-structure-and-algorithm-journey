#pragma once

#include <utility>

namespace td {
namespace utils {

// Specifies action which will be performed after `validate` method is called.
enum class Action {
  // Do nothing affect to container. Can be used in case getting an item value
  // from container.
  kNone,

  // Remove an item from container.
  kRemoved,

  // Insert an item to container.
  kInserted
};

// Determine `index` is within valid range or not. Incase `action`
// is `kInserted`, valid range is from 0 to `size`. Otherwise, it's
// from 0 to `size` - 1.
//
// If `index` is not valid or `action` is `kRemoved` and `size` is 0,
// throw an `std::out_of_range` exception.
void validate(std::size_t index, std::size_t size, Action action);

// Returns true if given number is a prime number. Otherwise, return false
bool is_prime(unsigned long long number);

// Returns smallest prime number which is equal or greater than given number.
unsigned long long next_prime(unsigned long long number);

}  // namespace utils
}  // namespace td
