#include <chrono>
#include <iostream>
#include <thread>
#include "IMU/IMU.h"
#include "common_types.h"
#include "fsr/fsr_reader.h"
#include "telemetry/server.h"

using namespace std;

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

  mcp3008Spi a2d("/dev/spidev0.0", SPI_MODE_0, 1000000, 8);
  int i = 20;
  int a2dVal = 0;
  int a2dChannel = 0;
  unsigned char pdata[3];

  sensors_data data = {};

  using clk = std::chrono::steady_clock;
  auto start_time = clk::now();

  while (1) {
    pdata[0] = 1;  //  first byte transmitted -> start bit
    pdata[1] =
        0b10'000'000;  // second byte transmitted -> (SGL/DIF = 1, D2=D1=D0=0)
    pdata[2] = 0;      // third byte transmitted....don't care

    a2d.spiWriteRead(pdata, sizeof(pdata));

    a2dVal = 0;
    a2dVal = (pdata[1] << 8) &
             0b1100000000;  // merge data[1] & data[2] to get result
    a2dVal |= (pdata[2] & 0xff);

    cout << "The Result is: " << a2dVal << endl;
    data.left.heel = a2dVal / 512.0f;

    // Second
    pdata[0] = 1;  //  first byte transmitted -> start bit
    pdata[1] =
        0b10'010'000;  // second byte transmitted -> (SGL/DIF = 1, D2=D1=D0=0)
    pdata[2] = 0;      // third byte transmitted....don't care

    a2d.spiWriteRead(pdata, sizeof(pdata));

    a2dVal = 0;
    a2dVal = (pdata[1] << 8) &
             0b1100000000;  // merge data[1] & data[2] to get result
    a2dVal |= (pdata[2] & 0xff);

    cout << "The Result is: " << a2dVal << endl;
    data.left.toe = a2dVal / 512.0f;

    // Third
    pdata[0] = 1;  //  first byte transmitted -> start bit
    pdata[1] =
        0b10'100'000;  // second byte transmitted -> (SGL/DIF = 1, D2=D1=D0=0)
    pdata[2] = 0;      // third byte transmitted....don't care

    a2d.spiWriteRead(pdata, sizeof(pdata));

    a2dVal = 0;
    a2dVal = (pdata[1] << 8) &
             0b1100000000;  // merge data[1] & data[2] to get result
    a2dVal |= (pdata[2] & 0xff);

    cout << "The Result is: " << a2dVal << endl;
    data.right.heel = a2dVal / 512.0f;

    // Fourth
    pdata[0] = 1;  //  first byte transmitted -> start bit
    pdata[1] =
        0b10'110'000;  // second byte transmitted -> (SGL/DIF = 1, D2=D1=D0=0)
    pdata[2] = 0;      // third byte transmitted....don't care

    a2d.spiWriteRead(pdata, sizeof(pdata));

    a2dVal = 0;
    a2dVal = (pdata[1] << 8) &
             0b1100000000;  // merge data[1] & data[2] to get result
    a2dVal |= (pdata[2] & 0xff);

    cout << "The Result is: " << a2dVal << endl;
    data.right.toe = a2dVal / 512.0f;

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

    float elapsed_s = std::chrono::duration_cast<std::chrono::milliseconds>(
                          clk::now() - start_time)
                          .count() /
                      1000.f;

    data.timepoint = elapsed_s;
    std::this_thread::sleep_for(std::chrono::milliseconds(25));
    server.broadcast(&data, sizeof(data));
  }
}
