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
  Sensor_IMU imu_1(get_mpu_fd_address());

  sensors_data data = {};

  while (1) {
    data.ax = imu_1.getAccel_X() / 16384.0;
    data.ay = imu_1.getAccel_Y() / 16384.0;
    data.az = imu_1.getAccel_Z() / 16384.0;

    data.gx = imu_1.getGyro_X() / 16384.0;
    data.gy = imu_1.getGyro_Y() / 16384.0;
    data.gz = imu_1.getGyro_Z() / 16384.0;

    printf("Accelerometer X: %.3f\n", data.ax);
    printf("Accelerometer Y: %.3f\n", data.ay);
    printf("Accelerometer Z: %.3f\n", data.az);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    server.broadcast(&data, sizeof(data));
  }
}
