#include "utils/utils.h"
#include "gtest/gtest.h"

namespace {

using namespace td::utils;

TEST(UtilsTest, Validate) {
  validate(1, 2, Action::kNone);
  EXPECT_THROW(validate(2, 2, Action::kNone), std::out_of_range);

  validate(10, 11, Action::kRemoved);
  EXPECT_THROW(validate(0, 0, Action::kRemoved), std::out_of_range);
  EXPECT_THROW(validate(1, 0, Action::kRemoved), std::out_of_range);

  validate(0, 0, Action::kInserted);
  validate(10, 10, Action::kInserted);
  EXPECT_THROW(validate(1, 0, Action::kInserted), std::out_of_range);
}

}  // namespace