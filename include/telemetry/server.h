#pragma once

#ifndef TELEMETRY_SERVER_H
#define TELEMETRY_SERVER_H

#include <memory>

namespace tel {

namespace detail {
class server_impl;
}  // namespace detail

class server {
 public:
  server();
  ~server();

  void run_on_thread(uint16_t port);
  void broadcast(const void *data, long len);

 private:
  std::unique_ptr<class detail::server_impl> m_server;
};

}  // namespace tel

#endif
