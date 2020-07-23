/**
 * @file controller.hpp
 * @brief Discription of the class "Controller".
 *
 * @details
 * The controller is a class "Observer". He receives a notification of a change
 * in the "Subject" and processes the information received.
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#ifndef CONTROLLER_HPP_
#define CONTROLLER_HPP_

#include <memory>
#include <string>

#include <libasync/common/cmdpool.hpp>
#include <libasync/common/counter.hpp>
#include <libasync/common/taskpool.hpp>
#include <libasync/io/ireader.hpp>
#include <libasync/utils/observer.hpp>

/** @brief The namespace of the Async Library project */
namespace libasync {
/** @brief The namespace of the Core */
namespace core {

/** @brief The controller is a class "Observer" */
class controller final : public utils::observer<std::string>,
                         public std::enable_shared_from_this<controller> {
  /** @brief Depth of nesting commands. */
  std::size_t depth_{0};

  /** @brief the count commands per block. */
  std::size_t commands_per_block_{0};

  common::counter counter_{};
  common::counter prev_cnt_{};

  /** @brief The pool of the commands. */
  std::unique_ptr<common::cmd_pool> pool_;

  /** @brief Pool for outputting log to console. */
  common::taskpool<1> console_pool_{"Console"};

  /** @brief Pool for outputting log to file. */
  common::taskpool<4> file_pool_{"File"};

  /** @brief The reader from console. */
  std::unique_ptr<io::ireader> reader_;

  std::ostream& ostrm_stat_;
  std::ostream& ostrm_log_;

  std::size_t id_;

public:
  /** @brief The default constructor. */
  controller() = delete;
  explicit controller(std::size_t id, std::size_t cmd_per_block,
                      std::unique_ptr<io::ireader> reader, std::ostream& ostrm_stat,
                      std::ostream& ostrm_log) noexcept;

  /** @brief The default distructor. */
  virtual ~controller() noexcept override;

  /**
   * @brief Update on the change in the state of the subject.
   * @param [in] str - data from subject.
   */
  void update(const std::string& str) override;

  /** @brief Start the process of receiving data. */
  void start();
  void stop() noexcept;

  /** @brief Resetting data from the command pool. */
  void flush();

  /**
   * @brief Setter to install number of commands in the block.
   * @param [in] value - number.
   */
  void set_commands_per_block(size_t value) noexcept {
    commands_per_block_ = value;
    //    pool_.set_pool_size(value);
  }

  /**
   * @brief Setter to install the reader.
   * @param [in] rdr - pointer to the reader.
   */
  //  void set_reader(std::shared_ptr<jjd::reader> rdr) noexcept {
  //    reader_ = rdr;
  //  }
};

} /* core:: */
} /* libasync:: */

#endif /* CONTROLLER_HPP_ */
