/**
 * @file context.cpp
 * @brief Implimentation of the class "Context".
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#include <iostream>
#include <ostream>

#include <libasync/common/split.hpp>
#include <libasync/core/context.hpp>
#include <libasync/io/tsreader.hpp>

/** @brief The namespace of the Async Library project */
namespace libasync {
/** @brief The namespace of the Core */
namespace core {

context::context(std::size_t id, std::size_t cmd_per_block) noexcept
  : ostrm_stat_{std::cout}, ostrm_log_{std::cout} {
  std::unique_ptr<io::ireader> rd = std::make_unique<io::tsreader>(queue_);
  controller_ =
      std::make_shared<core::controller>(id, cmd_per_block, std::move(rd), ostrm_stat_, ostrm_log_);

  worker_ = thread_ptr_t(new std::thread([this]() { controller_->start(); }),
                         [](std::thread* t) { t->join(); });
}

void context::input(const std::string& str) {
  std::vector<std::string> lines = common::split(str);

  for (std::string& line : lines) {
    queue_.push(std::move(line));
  }
}

void context::stop_wait() noexcept {
  while (!queue_.empty()) {
  }
  controller_->stop();
}

} /* core:: */
} /* libasync:: */
