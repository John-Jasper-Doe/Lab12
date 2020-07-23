/**
 * @file async.hpp
 * @brief Async functions for work with library..
 *
 * @date 2020
 */

#ifndef ASYNC_HPP_
#define ASYNC_HPP_

#include <cstddef>

/** @brief The namespace of the Async Library project */
namespace libasync {
/** @brief The namespace of the Async */
namespace async {

/** @brief Alias of the handler of type */
using handle_t = void*;

/**
 * @brief Create new execution
 * @param [in] bulk  - the number of commands in the block.
 * @return context pointer.
 */
handle_t connect(std::size_t bulk) noexcept;

/**
 * @brief Write data to a given context.
 * @param [in] handle - the context pointer.
 * @param [in] data - pointer on data.
 * @param [in] size - size data.
 */
void receive(handle_t handle, const char* data, std::size_t size) noexcept;

/**
 * @brief Destroy the context.
 * @param [in] handle - the context pointer.
 */
void disconnect(handle_t handle) noexcept;

} /* async:: */
} /* libasync:: */

#endif /* ASYNC_HPP_ */
