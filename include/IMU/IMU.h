#ifndef LIBIMU_H
#define LIBIMU_H

#include <stdint.h>

int get_mpu_fd_address();

class Sensor_IMU {
 public:
  Sensor_IMU(int fd, int pin);

  int getAccel_X();
  int getAccel_Y();
  int getAccel_Z();
  int getGyro_X();
  int getGyro_Y();
  int getGyro_Z();

 private:
  int read_i2c(int);

private:
  int fd;
  int pin;
};

#endif
