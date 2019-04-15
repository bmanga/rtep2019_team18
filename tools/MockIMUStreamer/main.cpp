#include <chrono>
#include <random>
#include <thread>
#include "common_types.h"
#include "telemetry/server.h"

std::random_device rd;

std::mt19937 gen(rd());
std::uniform_real_distribution<float> dist(1, 250);

imu_data random_packet()
{
  imu_data p;
  p.ax = dist(gen);
  p.ay = dist(gen);
  p.az = dist(gen);
  p.gx = dist(gen);
  p.gy = dist(gen);
  p.gz = dist(gen);

  return p;
}

sensors_data random_data()
{
  sensors_data sd;
  sd.a = random_packet();
  sd.b = random_packet();
  sd.c = random_packet();

  sd.left.heel = dist(gen);
  sd.left.toe = dist(gen);
  sd.right.heel = dist(gen);
  sd.right.toe = dist(gen);

  return sd;
}

int main()
{
  tel::server server;
  server.run_on_thread(9004);

  using clk = std::chrono::steady_clock;
  auto start_time = clk::now();

  while (1) {
    sensors_data data = random_data();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    float elapsed_s = std::chrono::duration_cast<std::chrono::milliseconds>(
                          clk::now() - start_time)
                          .count() /
                      1000.f;

    data.timepoint = elapsed_s;
    server.broadcast(&data, sizeof(data));
  }
}
