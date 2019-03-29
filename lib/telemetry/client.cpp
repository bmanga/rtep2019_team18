#include "telemetry/client.h"

#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>

#include <functional>
#include <mutex>
#include <string>
#include <thread>

namespace tel {
namespace ws = websocketpp;

namespace detail {
class client_impl {
  using client_t = websocketpp::client<websocketpp::config::asio_client>;

 public:
  client_impl() : m_message_handler(+[](const void *, long) {})
  {
    m_client.init_asio();

    using namespace ws::lib::placeholders;
    m_client.set_message_handler(
        ws::lib::bind(&client_impl::on_message, this, _1, _2));
  }

  ~client_impl()
  {
    if (m_client_thread.joinable())
      m_client_thread.join();
  }

  void run_on_thread()
  {
    m_client_thread = std::thread(&client_t::run, &m_client);
  }

  void set_message_handler(std::function<void(const void *, long)> fn)
  {
    m_message_handler = std::move(fn);
  }

  void connect_to(const std::string &uri)
  {
    ws::lib::error_code ec;
    client_t::connection_ptr conn = m_client.get_connection(uri, ec);

    if (ec) {
      std::cout << "could not create connection to " << uri << " :"
                << ec.message() << std::endl;
    }

    m_client.connect(conn);
  }

 private:
  void on_message(ws::connection_hdl, client_t::message_ptr msg)
  {
    const auto &payload = msg->get_raw_payload();
    m_message_handler(payload.data(), payload.length());
  }

 private:
  client_t m_client;
  std::thread m_client_thread;
  std::function<void(const void *, long)> m_message_handler;
};

}  // namespace detail

client::client() : m_client(std::make_unique<tel::detail::client_impl>()) {}

client::~client() = default;

void client::run_on_thread()
{
  m_client->run_on_thread();
}

void client::connect_to(const std::string &uri)
{
  m_client->connect_to(uri);
}

void client::set_message_handler(std::function<void(const void *, long)> fn)
{
  m_client->set_message_handler(std::move(fn));
}
}  // namespace tel
