/**
 * @file client.hpp
 * @brief Definition of the class "Client".
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <boost/asio.hpp>
#include <libasync/async/async.hpp>

namespace bulk_server {
namespace ba = boost::asio;

class client {
  ba::io_context& context_;
  ba::ip::tcp::socket socket_;
  libasync::async::handle_t handle_;

public:
  client() = delete;
  explicit client(ba::io_context& context, libasync::async::handle_t handle) noexcept;

  ~client() = default;

  client(const client&) = delete;
  client(client&&) = delete;

  client& operator=(const client&) = delete;
  client& operator=(client&&) = delete;
};

} /* bulk_server */

#endif /* CLIENT_HPP_ */
