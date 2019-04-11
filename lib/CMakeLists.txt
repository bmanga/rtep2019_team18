cmake_minimum_required(VERSION 3.8)
project(lib)

find_package(websocketpp REQUIRED)

add_library(telemetry
  telemetry/client.cpp
  telemetry/server.cpp)

target_include_directories(telemetry PRIVATE ../include)
target_link_libraries(telemetry PRIVATE websocketpp::websocketpp)

set(CMAKE_CXX_STANDARD 17)

add_library(wiringPi
  wiringPi/wiringPi.c
  wiringPi/wiringPiI2C.c
  wiringPi/softPwm.c
  wiringPi/softTone.c
  wiringPi/PiHiPri.c)

target_include_directories(wiringPi PRIVATE ../include)

add_library(imu
  IMU/IMU.cpp)

target_link_libraries(imu PRIVATE wiringPi)
target_include_directories(imu PRIVATE ../include)

add_library(fsr fsr/fsr_reader.cpp)
target_include_directories(fsr PRIVATE ../include)

