/**
 * @file ireader.hpp
 * @brief Discription of the interface class "IReader".
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#ifndef IREADER_HPP_
#define IREADER_HPP_

#include <string>

#include <libasync/utils/subject.hpp>

/** @brief The namespace of the Async Library project */
namespace libasync {
/** @brief The namespace of the IO */
namespace io {

class ireader : public utils::subject<std::string> {
public:
  virtual void read_cycle() = 0;
  virtual void stop_cycle() = 0;
};

} /* io:: */
} /* libasync:: */

#endif /* IREADER_HPP_ */
