/**
 * @file reader.cpp
 * @brief Implementation of the class "Reader".
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#include <istream>

#include <libasync/io/reader.hpp>

/** @brief The namespace of the Async Library project */
namespace libasync {
/** @brief The namespace of the IO */
namespace io {

reader::reader(std::istream& istrm) noexcept : istrm_{istrm} {}

reader::~reader() noexcept {}

void reader::read_cycle() {
  for (std::string tmp_str{""}; std::getline(istrm_, tmp_str);) {
    if (!tmp_str.empty())
      notify(tmp_str);
  }
}

void reader::stop_cycle() {}

} /* io:: */
} /* libasync:: */
