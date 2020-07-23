/**
 * @file ilogger.hpp
 * @brief Description of the interface class "ILogger".
 *
 * @details
 * Description of the general interface for logging in the program.
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#ifndef ILOGGER_HPP_
#define ILOGGER_HPP_

/** @brief The namespace of the Async Library project */
namespace libasync {

/** @brief The namespace of the Common */
namespace common {
class counter;
} /* common:: */

/** @brief The namespace of the IO */
namespace io {

/** @brief The "ILogger" class */
class ilogger {
public:
  ilogger() = default;
  virtual ~ilogger() = default;

  ilogger(const ilogger&) = delete;
  ilogger(ilogger&&) = delete;

  ilogger& operator=(const ilogger&) = delete;
  ilogger& operator=(ilogger&&) = delete;

  virtual common::counter start() noexcept = 0;
};

} /* io:: */
} /* libasync:: */

#endif /* ILOGGER_HPP_ */
