/**
 * @file subject.hpp
 *
 * @brief Discription of the template class "Subject".
 *
 * @details
 * Implemented "Subject" must be inherited from this class-template. When the
 * inherited "Subject" changes, it must notify all registered observers. Here
 * the basic functionality for work is implemented: registration, deletion and
 * notification of observers.
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#ifndef SUBJECT_HPP_
#define SUBJECT_HPP_

#include <algorithm>
#include <memory>
#include <vector>

#include "observer.hpp"

/** @brief The namespace of the Async Library project */
namespace libasync {
/** @brief The namespace of the Utils */
namespace utils {

/**
 * @brief Template class "Subject".
 * @tparam ARGS - template input parameters.
 */
template <typename... ARGS>
class subject {
  using observer_ptr_t = std::weak_ptr<observer<ARGS...>>;
  using observers_t = std::vector<observer_ptr_t>;

  /** @brief The observers list */
  observers_t observers_;

public:
  /** @brief The default constructor */
  subject() = default;

  /** @brief The default distructor (virtual) */
  virtual ~subject() = default;

  /**
   * @brief Add the observer.
   * @param [in] obs - pointer to the observer.
   */
  void attach(observer_ptr_t obs) {
    observers_.push_back(std::move(obs));
  }

  /**
   * @brief Remove the observer.
   * @param [in] obs - pointer to the observer.
   */
  void detach(observer_ptr_t obs) {
    if (auto spt = obs.lock()) {
      auto weak_cmp = [&spt](const observer_ptr_t& o) { return spt == o.lock(); };

      auto it = std::find_if(observers_.cbegin(), observers_.cend(), weak_cmp);
      if (it != observers_.cend())
        observers_.erase(it);
    }
  }

protected:
  /**
   * @brief Notify all observers.
   * @param [in] args - arguments that are passed to observers.
   */
  void notify(const ARGS&... args) {
    for (const auto& obs : observers_) {
      if (auto spt = obs.lock())
        spt->update(args...);
    }
  }
};

} /* utils:: */
} /* libasync:: */

#endif /* SUBJECT_HPP_ */
