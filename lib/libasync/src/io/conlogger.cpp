/**
 * @file conlogger.cpp
 * @brief Implementation of the "Console Logger" class.
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#include <libasync/io/conlogger.hpp>

/** @brief The namespace of the Async Library project */
namespace libasync {
/** @brief The namespace of the IO */
namespace io {

conlogger::conlogger(std::ostream& ostrm, const std::string& str,
                     const common::counter& cnt) noexcept
  : ostrm_(ostrm), str_(std::move(str)), cnt_(cnt) {}

conlogger::~conlogger() noexcept {}

common::counter conlogger::start() noexcept {
  ostrm_ << str_ << '\n' << std::flush;
  return cnt_;
}

} /* io:: */
} /* libasync:: */
