#include <gtest/gtest.h>
#include <libasync/common/cmdpool.hpp>

TEST(test_cmd_pool, test_size) {
  libasync::common::cmd_pool pool;
  ASSERT_EQ(pool.size(), 0);

  pool.add("cmd1");
  ASSERT_EQ(pool.size(), 1);

  pool.add("cmd2");
  ASSERT_EQ(pool.size(), 2);

  pool.clear();
  ASSERT_EQ(pool.size(), 0);
}

TEST(test_cmd_pool, test_as_str) {
  libasync::common::cmd_pool pool;
  pool.add("cmd1");
  pool.add("cmd2");
  pool.add("cmd3");
  pool.add("cmd4");

  std::stringstream ss{"bulk: cmd1, cmd2, cmd3, cmd4"};
  ASSERT_EQ(pool.as_str(), ss.str());

  pool.clear();
  pool.add("cmd1");
  pool.add("cmd2");

  ss.str("bulk: cmd1, cmd2");
  ASSERT_EQ(pool.as_str(), ss.str());
}
