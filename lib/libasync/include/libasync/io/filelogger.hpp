/**
 * @file filelogger.hpp
 * @brief Discription of the "File Logger" class.
 *
 * @details
 * Class for logging data to the file.
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#ifndef FILELOGGER_HPP_
#define FILELOGGER_HPP_

#include <chrono>
#include <string>

#include <libasync/common/counter.hpp>
#include <libasync/io/ilogger.hpp>

/** @brief The namespace of the Async Library project */
namespace libasync {
/** @brief The namespace of the IO */
namespace io {

using time_point_t = std::chrono::time_point<std::chrono::system_clock>;

/** @brief Logger for print bulk in file and console. */
class filelogger final : public libasync::io::ilogger {
  std::string str_;
  time_point_t time_point_;
  libasync::common::counter cnt_;

public:
  /**
   * @brief The construcor.
   * @param [in] str - text to output to the log.
   * @param [in] time_point - time point.
   * @param [in] cnt - counter for accounting.
   */
  explicit filelogger(const std::string& str, time_point_t time_point,
                      const libasync::common::counter& cnt) noexcept;

  /** @brief The default distructor. */
  virtual ~filelogger() noexcept override;

  /**
   * @brief start
   * @return Counter for accounting.
   */
  virtual libasync::common::counter start() noexcept override;
};

} /* io:: */
} /* libasync:: */

#endif /* FILELOGGER_HPP_ */
