/**
 * @file filelogger.cpp
 * @brief Implementation of the "File Logger" class.
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>

#include <libasync/io/filelogger.hpp>

/** @brief The namespace of the Async Library project */
namespace libasync {
/** @brief The namespace of the IO */
namespace io {

filelogger::filelogger(const std::string& str, time_point_t time_point,
                       const libasync::common::counter& cnt) noexcept
  : str_(std::move(str)), time_point_(time_point), cnt_(cnt) {}

filelogger::~filelogger() noexcept {}

common::counter filelogger::start() noexcept {
  std::stringstream file_name;
  file_name << std::to_string(time_point_.time_since_epoch().count()) << "_"
            << std::this_thread::get_id() << ".log";

  std::ofstream file(file_name.str());
  if (file.is_open()) {
    file << str_ << '\n';
    file.close();
  }
  else {
    std::cerr << "Error opening file" << std::endl;
  }
  return cnt_;
}

} /* io:: */
} /* libasync:: */
