#include "telemetry/server.h"

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <cstdint>
#include <mutex>
#include <set>
#include <thread>

namespace ws = websocketpp;

namespace tel {
namespace detail {

class server_impl {
  using server_t = ws::server<ws::config::asio>;

 public:
  server_impl()
  {
    using namespace ws::lib::placeholders;
    m_server.init_asio();

    m_server.set_open_handler(ws::lib::bind(&server_impl::on_open, this, _1));
    m_server.set_close_handler(ws::lib::bind(&server_impl::on_close, this, _1));
  }
  ~server_impl()
  {
    m_server.stop();
    m_server_thread.join();
  }

  void broadcast(const void *data, size_t len)
  {
    lock l(m_mutex);
    for (auto connection : m_connections) {
      m_server.send(connection, data, len, ws::frame::opcode::BINARY);
    }
  }

  void run_on_thread(uint16_t port)
  {
    lock l(m_mutex);
    m_server.listen(port);
    m_server.start_accept();
    m_server_thread = std::thread(&server_t::run, &m_server);
  }

 private:
  void on_open(ws::connection_hdl hdl)
  {
    lock l(m_mutex);
    m_connections.insert(hdl);
  }
  void on_close(ws::connection_hdl hdl)
  {
    lock l(m_mutex);
    m_connections.erase(hdl);
  }

 private:
  server_t m_server;
  std::set<ws::connection_hdl, std::owner_less<ws::connection_hdl>>
      m_connections;
  std::mutex m_mutex;
  using lock = std::lock_guard<std::mutex>;
  std::thread m_server_thread;
};

}  // namespace detail

server::server() : m_server(std::make_unique<detail::server_impl>()) {}

server::~server() = default;

void server::run_on_thread(uint16_t port)
{
  m_server->run_on_thread(port);
}

void server::broadcast(const void *data, long len)
{
  m_server->broadcast(data, len);
}
}  // namespace tel