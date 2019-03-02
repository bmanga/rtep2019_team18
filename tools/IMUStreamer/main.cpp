#include <thread>
#include "IMU/IMU.h"
#include "telemetry/server.h"

struct sensors_data {
  float ax, ay, az;
  float gx, gy, gz;
};

int main()
{
  tel::server server;
  server.run_on_thread(9006);

  Sensor_IMU imu_1(0);
  Sensor_IMU imu_2(2);

  sensors_data data = {};

  while (1) {
    data.ax = imu_1.getAccel_X() / 16384.0;
    data.ay = imu_1.getAccel_Y() / 16384.0;
    data.az = imu_1.getAccel_Z() / 16384.0;

    data.gx = imu_1.getGyro_X() / 16384.0;
    data.gy = imu_1.getGyro_Y() / 16384.0;
    data.gz = imu_1.getGyro_Z() / 16384.0;

    printf("Accelerometer (A) X: %.3f\n", data.ax);
    printf("Accelerometer (A) Y: %.3f\n", data.ay);
    printf("Accelerometer (A) Z: %.3f\n", data.az);

    printf("Accelerometer (B) X: %.3f\n", imu_2.getAccel_X() / 16384.0);
    printf("Accelerometer (B) Y: %.3f\n", imu_2.getAccel_Y() / 16384.0);
    printf("Accelerometer (B) Z: %.3f\n", imu_2.getAccel_Z() / 16384.0);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    server.broadcast(&data, sizeof(data));
  }
}
