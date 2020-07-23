/**
 * @file reader.hpp
 * @brief Discription of the class "Reader".
 *
 * @details
 * Description of the class "Reader", which in the "Observer" pattern
 * implements the "Subject". The class "Reader" is inherited from the template
 * "Subject" and performs the function of receiving data from the input stream
 * and notifies all observers who are subscribed to it.
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#ifndef READER_HPP_
#define READER_HPP_

#include <libasync/io/ireader.hpp>

/** @brief The namespace of the Async Library project */
namespace libasync {
/** @brief The namespace of the IO */
namespace io {

/** @brief The reader class */
class reader final : public io::ireader {
  /** @brief The input stream. */
  std::istream& istrm_;

public:
  /**
   * @brief The constructor with parameters.
   * @param [in] istrm - the input stream.
   */
  explicit reader(std::istream& istrm) noexcept;

  virtual ~reader() noexcept override;

  /** @brief Loop to read data from the input stream. */
  virtual void read_cycle() override;
  virtual void stop_cycle() override;
};

} /* io:: */
} /* libasync:: */

#endif /* READER_HPP_ */
