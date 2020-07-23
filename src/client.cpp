/**
 * @file client.cpp
 * @brief Implimentation of the class "Client".
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#include "client.hpp"

namespace bulk_server {

client::client(boost::asio::io_context& context, libasync::async::handle_t handle) noexcept
  : context_(context), socket_(context_), handle_(handle) {}

} /* bulk_server */
