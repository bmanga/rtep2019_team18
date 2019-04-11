#include <iostream>
#include <thread>
#include "IMU/IMU.h"
#include "fmt/format.h"
#include "telemetry/server.h"

struct sensors_data {
  float ax, ay, az;
  float gx, gy, gz;
};

struct fsr_data {
  float a, b;
};

struct packet {
  sensors_data a, b, c;
  fsr_data x, y;
};

int main()
{
  tel::server server;
  server.run_on_thread(9004);

  Sensor_IMU imu_1(0);
  Sensor_IMU imu_2(2);
  Sensor_IMU imu_3(3);

  imu_1.initialize();
  imu_2.initialize();
  imu_3.initialize();

  packet data = {};

  while (1) {
    data = {};
    data.a.ax = imu_1.getAccel_X() / 16384.0;
    data.a.ay = imu_1.getAccel_Y() / 16384.0;
    data.a.az = imu_1.getAccel_Z() / 16384.0;
    data.a.gx = imu_1.getGyro_X() / 16384.0;
    data.a.gy = imu_1.getGyro_Y() / 16384.0;
    data.a.gz = imu_1.getGyro_Z() / 16384.0;

    data.b.ax = imu_2.getAccel_X() / 16384.0;
    data.b.ay = imu_2.getAccel_Y() / 16384.0;
    data.b.az = imu_2.getAccel_Z() / 16384.0;
    data.b.gx = imu_2.getGyro_X() / 16384.0;
    data.b.gy = imu_2.getGyro_Y() / 16384.0;
    data.b.gz = imu_2.getGyro_Z() / 16384.0;

    data.c.ax = imu_3.getAccel_X() / 16384.0;
    data.c.ay = imu_3.getAccel_Y() / 16384.0;
    data.c.az = imu_3.getAccel_Z() / 16384.0;
    data.c.gx = imu_3.getGyro_X() / 16384.0;
    data.c.gy = imu_3.getGyro_Y() / 16384.0;
    data.c.gz = imu_3.getGyro_Z() / 16384.0;

    std::cout << fmt::format(
                     "A: {: f} {: f} {: f} -- B: {: f} {: f} {: f} -- C: {: f} "
                     "{: f} {: f}",
                     data.a.ax, data.a.ay, data.a.az, data.b.ax, data.b.ay,
                     data.b.az, data.c.ax, data.c.ay, data.c.az)
              << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    server.broadcast(&data, sizeof(data));
  }
}
