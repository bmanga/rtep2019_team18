#include <iostream>
#include "telemetry/client.h"

void on_message(const void *d, long len) {}

int main(int argc, char *argv[])
{
  if (argc != 2) {
    std::cout << "Invalid number of arguments: Requires  only the "
                 "address of the streamer server to connect to.";
    return -1;
  }

  tel::client client;
  client.set_message_handler(&on_message);

  client.connect_to(argv[1]);
  client.run_on_thread();
}
