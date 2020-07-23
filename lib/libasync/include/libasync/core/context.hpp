/**
 * @file context.hpp
 * @brief Discription of the class "Context".
 *
 * @details
 * Execution context for async connectons. This context allows you to control
 * the program.
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#ifndef CONTEXT_HPP_
#define CONTEXT_HPP_

#include <memory>
#include <string>
#include <thread>

#include <libasync/common/tsqueue.hpp>
#include <libasync/core/controller.hpp>

/** @brief The namespace of the Async Library project */
namespace libasync {
/** @brief The namespace of the Core */
namespace core {

/** @brief The controller is a class "Observer" */
class context final {
  /** @brief Thread poll alias. */
  using thread_ptr_t = std::unique_ptr<std::thread, std::function<void(std::thread*)>>;
  /** @brief Alias of the thread-safe queue of type. */
  using tsqueue_t = common::tsqueue<std::string>;

  //  /** @brief the count commands per block. */
  //  std::size_t cmd_per_block_{0};

  std::shared_ptr<libasync::core::controller> controller_;

  /** @brief "Workhorse" context. */
  thread_ptr_t worker_;

  tsqueue_t queue_;
  std::ostream& ostrm_stat_;
  std::ostream& ostrm_log_;

public:
  /** @brief The default constructor. */
  context() = delete;
  explicit context(std::size_t id, std::size_t cmd_per_block) noexcept;

  /** @brief The default distructor. */
  ~context() = default;

  context(context&&) = delete;
  context& operator=(context&&) = delete;

  context(const context&) = delete;
  context& operator=(const context&) = delete;

  void input(const std::string& str);
  void stop_wait() noexcept;
};

} /* core:: */
} /* libasync:: */

#endif /* CONTEXT_HPP_ */
