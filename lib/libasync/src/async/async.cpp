/**
 * @file async.cpp
 * @brief Async functions for work with library..
 *
 * @date 2020
 */

#include <map>
#include <memory>
#include <mutex>

#include <libasync/async/async.hpp>
#include <libasync/core/context.hpp>

/** @brief The namespace of the Async Library project */
namespace libasync {
/** @brief The namespace of the Async */
namespace async {

using raw_context_ptr_t = core::context*;
using context_ptr_t = std::unique_ptr<core::context>;

namespace {

/* Context */
static std::map<raw_context_ptr_t, context_ptr_t> contexts;
static std::size_t context_id = 0;
static std::mutex mtx;

} /* :: */

handle_t connect(std::size_t bulk) noexcept {
  try {
    std::unique_lock<std::mutex> lock(mtx);
    context_ptr_t ptr = std::make_unique<core::context>(++context_id, bulk);
    raw_context_ptr_t raw_ptr = ptr.get();

    contexts.emplace(std::make_pair(raw_ptr, std::move(ptr)));
    lock.unlock();

    return reinterpret_cast<handle_t>(raw_ptr);
  }
  catch (...) {
    return nullptr;
  }
}

void receive(handle_t handle, const char* data, std::size_t size) noexcept {
  std::unique_lock<std::mutex> lock(mtx);

  auto it = contexts.find(reinterpret_cast<raw_context_ptr_t>(handle));
  if (it != contexts.end()) {
    lock.unlock();
    it->second->input(std::string(data, size));
  }
}

void disconnect(handle_t handle) noexcept {
  std::unique_lock<std::mutex> lock(mtx);

  auto it = contexts.find(reinterpret_cast<raw_context_ptr_t>(handle));
  if (it != contexts.end()) {
    lock.unlock();

    it->second->stop_wait();
    it->second.reset();

    lock.lock();
    contexts.erase(it);
  }
}

} /* async:: */
} /* libasync:: */
