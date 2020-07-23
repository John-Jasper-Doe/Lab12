/**
 * @file cmdpool.hpp
 * @brief Discription of the class "cmd_pool".
 *
 * @details
 * Class description "Pool". This class is intended for storing commands and
 * their further reset to the console or to a file.
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#ifndef CMDPOOL_HPP_
#define CMDPOOL_HPP_

#include <chrono>
#include <sstream>
#include <string>
#include <vector>

/** @brief The namespace of the Async Library project */
namespace libasync {
/** @brief The namespace of the Common */
namespace common {

/** @brief Alias of the commands pool of type. */
using cmd_t = std::string;
/** @brief Alias of the commands pool of type. */
using pool_t = std::vector<cmd_t>;
/** @brief Alias of the time of the first command added to the pool. */
using first_cmd_time_t = std::chrono::time_point<std::chrono::system_clock>;

/** @brief The "cmd_pool" class. */
class cmd_pool final {
  /** @brief The pool of the commands. */
  pool_t pool_{};

  /** @brief The first command time. */
  first_cmd_time_t first_cmd_time_{};

public:
  /** @brief The constructor. */
  cmd_pool() = default;

  /** @brief The default distructor. */
  ~cmd_pool() = default;

  /**
   * @brief Adding a command to the pool.
   * @param [in] cmd - the command.
   */
  void add(const cmd_t&& cmd);

  /**
   * @brief Number of the commands in the pool.
   * @return Pool size.
   */
  std::size_t size() const;

  /**
   * @brief Gte first command time.
   * @return First command time.
   */
  first_cmd_time_t first_cmd_time() const;

  /**
   * @brief Get the pool of the commands as string.
   * @return String of the commands.
   */
  std::string as_str() const;

  /** @brief Clear the pool. */
  void clear();
};

} /* common:: */
} /* libasync:: */

#endif /* CMDPOOL_HPP_ */
