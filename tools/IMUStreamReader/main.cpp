#include <cassert>
#include <cstring>
#include <thread>
#include "telemetry/client.h"

struct sensors_data {
  float ax, ay, az;
  float gx, gy, gz;
};

void on_message(const void *d, long len)
{
  assert(len == sizeof(sensors_data));
  sensors_data data;
  memcpy(&data, d, len);

  printf("Accelerometer X: %.3f\n", data.ax);
  printf("Accelerometer Y: %.3f\n", data.ay);
  printf("Accelerometer Z: %.3f\n", data.az);

  printf("Gyroscope X: %.3f\n", data.gx);
  printf("Gyroscope Y: %.3f\n", data.gy);
  printf("Gyroscope Z: %.3f\n", data.gz);
}
int main()
{
  tel::client client;
  client.set_message_handler(&on_message);
  client.connect_to("ws://localhost:9006");

  client.run_on_thread();
}