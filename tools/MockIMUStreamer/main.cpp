#include <random>
#include <thread>
#include "telemetry/server.h"

struct imu_packet {
  float ax, ay, az;
  float gx, gy, gz;
};

struct fsr_packet {
  float heel, toe;
};

struct sensors_data {
  imu_packet p1, p2, p3;
  fsr_packet left, right;
};

std::random_device rd;

std::mt19937 gen(rd());
std::uniform_real_distribution<float> dist(1, 49);

imu_packet random_packet()
{
  imu_packet p;
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
  sd.p1 = random_packet();
  sd.p2 = random_packet();
  sd.p3 = random_packet();

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

  while (1) {
    sensors_data data = random_data();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    server.broadcast(&data, sizeof(data));
  }
}
