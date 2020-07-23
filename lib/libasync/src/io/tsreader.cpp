/**
 * @file tsreader.cpp
 * @brief Implementation of the class "TsReader".
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#include <iostream>

#include <libasync/io/tsreader.hpp>

/** @brief The namespace of the Async Library project */
namespace libasync {
/** @brief The namespace of the IO */
namespace io {

tsreader::tsreader(tsqueue_t& iqueue) noexcept : queue_{iqueue} {}

tsreader::~tsreader() noexcept {}

void tsreader::read_cycle() {
  while (!stopped_) {
    std::string res{""};

    if (queue_.try_pop(res)) {
      if (!res.empty())
        notify(res);
    }
  }
}

void tsreader::stop_cycle() {
  stopped_ = true;
}

} /* io:: */
} /* libasync:: */
