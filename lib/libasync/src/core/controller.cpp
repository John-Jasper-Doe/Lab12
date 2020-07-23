/**
 * @file controller.cpp
 * @brief The implementation of the class "Controller".
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#include <iostream>

#include <libasync/common/counter.hpp>
#include <libasync/core/controller.hpp>
#include <libasync/io/conlogger.hpp>
#include <libasync/io/filelogger.hpp>

/** @brief The namespace of the Async Library project */
namespace libasync {
/** @brief The namespace of the Core */
namespace core {

controller::controller(std::size_t id, std::size_t cmd_per_block,
                       std::unique_ptr<io::ireader> reader, std::ostream& ostrm_stat,
                       std::ostream& ostrm_log) noexcept
  : commands_per_block_(cmd_per_block)
  , pool_(std::make_unique<common::cmd_pool>())
  , reader_(std::move(reader))
  , ostrm_stat_(ostrm_stat)
  , ostrm_log_(ostrm_log)
  , id_{id} {}

controller::~controller() noexcept {
  if (pool_->size() > 0 && depth_ == 0)
    flush();

  stop();
  console_pool_.stop();
  file_pool_.stop();

  ostrm_stat_ << "[" << id_ << "]: All stats: " << counter_.as_str(true) << std::endl;
  ostrm_stat_ << console_pool_.count_as_str() << std::endl;
  ostrm_stat_ << file_pool_.count_as_str() << std::endl;
}

void controller::start() {
  console_pool_.start();
  file_pool_.start();

  auto this_ptr = shared_from_this();
  std::weak_ptr<controller> weak_ptr(this_ptr);
  reader_->attach(weak_ptr);
  reader_->read_cycle();
  reader_->detach(weak_ptr);
}

void controller::stop() noexcept {
  reader_->stop_cycle();
}

void controller::update(const std::string& str) {
  if (!str.empty()) {
    counter_.inc_str();

    if (str == "{") {
      if (depth_ == 0) {
        flush();
        ++depth_;
      }
      else
        ++depth_;
    }
    else if (str == "}") {
      if (depth_ == 0)
        throw std::runtime_error("invalid closed block without opened ones");
      else {
        --depth_;

        if (depth_ == 0) {
          counter_.inc_blk();
          flush();
        }
      }
    }
    else {
      counter_.inc_cmd();
      pool_->add(std::move(str));

      if (depth_ == 0 && pool_->size() == commands_per_block_)
        flush();
    }
  }
}

void controller::flush() {
  if (pool_->size() > 0) {
    common::counter diff = counter_ - prev_cnt_;
    std::string str = pool_->as_str();
    pool_->clear();

    std::shared_ptr<io::filelogger> fl =
        std::make_shared<io::filelogger>(str, pool_->first_cmd_time(), diff);
    std::shared_ptr<io::conlogger> cl = std::make_shared<io::conlogger>(ostrm_log_, str, diff);

    file_pool_.push([fl]() { return fl->start(); });
    console_pool_.push([cl]() { return cl->start(); });

    prev_cnt_ = counter_;
  }
}

} /* core:: */
} /* libasync:: */
