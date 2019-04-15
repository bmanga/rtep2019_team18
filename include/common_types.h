#ifndef RTEP_TEAM18_COMMON_TYPES_H
#define RTEP_TEAM18_COMMON_TYPES_H

struct imu_data {
  float ax, ay, az;
  float gx, gy, gz;
};

struct fsr_data {
  float toe, heel;
};

struct sensors_data {
  float timepoint;
  imu_data a, b, c;
  fsr_data left, right;
};

#endif  // RTEP_TEAM18_COMMON_TYPES_H
