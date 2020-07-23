/**
 * @file counter.hpp
 * @brief Discription of the class "counter".
 *
 * @details
 * Class description "Counter". This class describes counters for counting
 * commands and other necessary program elements.
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#ifndef COUNTER_HPP_
#define COUNTER_HPP_

#include <chrono>
#include <sstream>
#include <string>
#include <vector>

/** @brief The namespace of the Async Library project */
namespace libasync {
/** @brief The namespace of the Common */
namespace common {

/** @brief The "counter" class. */
class counter final {
  /** @brief The string counter. */
  std::size_t str_{0};

  /** @brief The command counter. */
  std::size_t cmd_{0};

  /** @brief The block counter. */
  std::size_t blk_{0};

public:
  /** @brief The constructor. */
  counter() = default;

  /** @brief The default distructor. */
  ~counter() = default;

  /** @brief Instructs a string count counter. */
  void inc_str() noexcept;

  /** @brief Instructs a command count counter. */
  void inc_cmd() noexcept;

  /** @brief Instructs a block count counter. */
  void inc_blk() noexcept;

  /**
   * @brief The output of the counting results as a string of text.
   * @param [in] allow_strings_cnt - Output permission flag with the results of
   *                                 the number of lines.
   * @return The result is a line of text.
   */
  std::string as_str(bool allow_strings_cnt = false) noexcept;

  friend counter& operator+=(counter& lhs, const counter& rhs);
  friend counter& operator-=(counter& lhs, const counter& rhs);

  friend counter operator+(counter& lhs, const counter& rhs);
  friend counter operator-(counter& lhs, const counter& rhs);
};

inline counter& operator+=(counter& lhs, const counter& rhs) {
  lhs.str_ += rhs.str_;
  lhs.cmd_ += rhs.cmd_;
  lhs.blk_ += rhs.blk_;

  return lhs;
}

inline counter& operator-=(counter& lhs, const counter& rhs) {
  lhs.str_ -= rhs.str_;
  lhs.cmd_ -= rhs.cmd_;
  lhs.blk_ -= rhs.blk_;

  return lhs;
}

inline counter operator+(counter& lhs, const counter& rhs) {
  counter res;

  res.str_ = lhs.str_ + rhs.str_;
  res.cmd_ = lhs.cmd_ + rhs.cmd_;
  res.blk_ = lhs.blk_ + rhs.blk_;

  return res;
}

inline counter operator-(counter& lhs, const counter& rhs) {
  counter res;

  res.str_ = lhs.str_ - rhs.str_;
  res.cmd_ = lhs.cmd_ - rhs.cmd_;
  res.blk_ = lhs.blk_ - rhs.blk_;

  return res;
}

} /* common:: */
} /* libasync:: */

#endif /* COUNTER_HPP_ */
