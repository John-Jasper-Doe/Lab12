/**
 * @file counter.cpp
 * @brief Implementation of the class "counter".
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#include <libasync/common/counter.hpp>

/** @brief The namespace of the Async Library project */
namespace libasync {
/** @brief The namespace of the Common */
namespace common {

void counter::inc_str() noexcept {
  ++str_;
}

void counter::inc_cmd() noexcept {
  ++cmd_;
}

void counter::inc_blk() noexcept {
  ++blk_;
}

std::string counter::as_str(bool allow_strings_cnt) noexcept {
  std::string res{""};

  if (allow_strings_cnt)
    res.append(std::to_string(str_) + " strings, ");

  res.append(std::to_string(cmd_) + " commands, " + std::to_string(blk_) + " blocks");
  return res;
}

} /* common:: */
} /* libasync:: */
