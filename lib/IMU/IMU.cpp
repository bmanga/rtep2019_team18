#include "IMU/IMU.h"
#include <stdio.h>
#include <wiringPi/wiringPi.h>
#include <wiringPi/wiringPiI2C.h>
#include <cstdlib>

#define ACCEL_X 0x3B
#define ACCEL_Y 0x3D
#define ACCEL_Z 0x3F

#define GYRO_X 0x43
#define GYRO_Y 0x45
#define GYRO_Z 0x47

#define MPU_6050_POWER_MGMT 0x6B

static int intial_setup = wiringPiSetup();
static int fd = wiringPiI2CSetup(0x68);

static int read_i2c(int pin, int addr)
{
  digitalWrite(pin, LOW);
  int val, high_byte, low_byte = 0;
  high_byte = wiringPiI2CReadReg8(fd, addr);

  low_byte = wiringPiI2CReadReg8(fd, addr + 1);
  val = (high_byte << 8) | low_byte;
  if (val >= 0x8000) {
    val = -(65536 - val);
  }
  digitalWrite(pin, HIGH);

  return val;
}

Sensor_IMU::Sensor_IMU(int pin) : pin(pin)
{
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  wiringPiI2CReadReg8(fd, MPU_6050_POWER_MGMT);
  // disable sleep mode
  wiringPiI2CWriteReg8(fd, MPU_6050_POWER_MGMT, 0);
  digitalWrite(pin, HIGH);
}

int Sensor_IMU::getAccel_X()
{
  int accel_X = 0;
  accel_X = read_i2c(pin, ACCEL_X);
  return accel_X;
}

int Sensor_IMU::getAccel_Y()
{
  int accel_Y = 0;
  accel_Y = read_i2c(pin, ACCEL_Y);
  return accel_Y;
}

int Sensor_IMU::getAccel_Z()
{
  int accel_Z = 0;
  accel_Z = read_i2c(pin, ACCEL_Z);
  return accel_Z;
}

int Sensor_IMU::getGyro_X()
{
  int gyro_X = 0;
  gyro_X = read_i2c(pin, GYRO_X);
  return gyro_X;
}

int Sensor_IMU::getGyro_Y()
{
  int gyro_Y = 0;
  gyro_Y = read_i2c(pin, GYRO_Y);
  return gyro_Y;
}

int Sensor_IMU::getGyro_Z()
{
  int gyro_Z = 0;
  gyro_Z = read_i2c(pin, GYRO_Z);
  return gyro_Z;
}
