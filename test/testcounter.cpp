#include <gtest/gtest.h>
#include <libasync/common/counter.hpp>

TEST(test_counter, test_inc) {
  libasync::common::counter cnt;

  cnt.inc_blk();
  cnt.inc_cmd();
  cnt.inc_str();

  std::string expected{"1 strings, 1 commands, 1 blocks"};
  ASSERT_EQ(cnt.as_str(true), expected);

  expected.clear();
  expected.append("1 commands, 1 blocks");
  ASSERT_EQ(cnt.as_str(), expected);
}
