#ifndef LIBIMU_H
#define LIBIMU_H

#include <stdint.h>

class Sensor_IMU {
 public:
  Sensor_IMU(int pin);

  int getAccel_X();
  int getAccel_Y();
  int getAccel_Z();
  int getGyro_X();
  int getGyro_Y();
  int getGyro_Z();

 private:
  int pin;
};

#endif
