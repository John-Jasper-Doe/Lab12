/**
 * @file observer.hpp
 *
 * @brief Discription of the template class "Observer".
 *
 * @details
 * The base class of the "Observer" object template. It provides basic
 * functionality to all inherited objects. All observers must inherit from it.
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#ifndef OBSERVER_HPP_
#define OBSERVER_HPP_

/** @brief The namespace of the Async Library project */
namespace libasync {
/** @brief The namespace of the Utils */
namespace utils {

/**
 * @brief Template class "Observer".
 * @tparam ARGS - template input parameters.
 */
template <typename... ARGS>
class observer {
public:
  /** @brief The default constructor */
  observer() = default;

  /** @brief The default distructor */
  virtual ~observer() = default;

  /** @brief update all observer */
  virtual void update(const ARGS&...) = 0;
};

} /* utils:: */
} /* bullktm:: */

#endif /* OBSERVER_HPP_ */
