/**
 * @file tsreader.hpp
 * @brief Discription of the class "TsReader".
 *
 * @details
 * Description of the class "TsReader", which in the "Observer" pattern
 * implements the "Subject". The class "Reader" is inherited from the template
 * "Subject" and performs the function of receiving data from the input stream
 * and notifies all observers who are subscribed to it.
 *
 * @note Thread-safe class modification.
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#ifndef TSREADER_HPP_
#define TSREADER_HPP_

#include <atomic>

#include <libasync/common/tsqueue.hpp>
#include <libasync/io/ireader.hpp>

/** @brief The namespace of the Async Library project */
namespace libasync {
/** @brief The namespace of the IO */
namespace io {

/** @brief Alias of the thread-safe queue of type. */
using tsqueue_t = common::tsqueue<std::string>;

/** @brief The tsreader class */
class tsreader final : public io::ireader {
  /** @brief Flag alias. */
  using flag_t = std::atomic<bool>;

  /** @brief The input queue. */
  tsqueue_t& queue_;
  flag_t stopped_{false};

public:
  /**
   * @brief The constructor with parameters.
   * @param [in] iqueue - the input queue.
   */
  explicit tsreader(tsqueue_t& iqueue) noexcept;

  virtual ~tsreader() noexcept override;

  /** @brief Loop to read data from the input stream. */
  virtual void read_cycle() override;
  virtual void stop_cycle() override;
};

} /* io:: */
} /* libasync:: */

#endif /* TSREADER_HPP_ */
