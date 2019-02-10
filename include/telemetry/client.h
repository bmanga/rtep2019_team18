#pragma once

#ifndef TELEMETRY_CLIENT_H
#define TELEMETRY_CLIENT_H

#include <functional>
#include <memory>
#include <string>

namespace tel {

namespace detail {
class client_impl;
}

class client {
 public:
  client();
  ~client();
  void connect_to(const std::string &uri);
  void set_message_handler(std::function<void(const void *, long)> fn);
  void run_on_thread();

 private:
  std::unique_ptr<detail::client_impl> m_client;
};
}  // namespace tel

#endif
