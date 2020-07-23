/**
 * @file client.cpp
 * @brief Implimentation of the class "Client".
 *
 * @author Maxim <john.jasper.doe@gmail.com>
 * @date 2020
 */

#include "client.hpp"
#include <boost/bind.hpp>

namespace bulk_server {

client::client(boost::asio::io_context& context, libasync::async::handle_t handle) noexcept
  : context_(context), socket_(context_), handle_(handle) {}

void client::start() noexcept {
  stopped_ = false;
  do_read();
}

void client::stop() noexcept {
  if (stopped_)
    return;
  else {
    stopped_ = true;
    socket_.close();
  }
}

void client::do_read() noexcept {
  if (stopped_)
    return;
  else {
    ba::async_read_until(
        socket_, buffer_, '\n',
        boost::bind(&client::read, shared_from_this(), boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
  }
}

void client::read(const boost::system::error_code& ec, std::size_t sz) noexcept {
  if (ec == boost::asio::error::eof || ec == boost::asio::error::connection_reset)
    stop();
  else if (stopped_)
    return;
  else {
    if (sz != 0) {
      std::istream out_strm(&buffer_);
      std::string command;
      getline(out_strm, command);
      command += '\n';
      libasync::async::receive(handle_, command.c_str(), sz);
    }

    do_read();
  }
}

} /* bulk_server */
