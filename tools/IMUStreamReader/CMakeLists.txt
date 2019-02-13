cmake_minimum_required(VERSION 3.8)

add_executable(imu-stream-reader main.cpp)
target_link_libraries(imu-stream-reader PRIVATE telemetry)
target_include_directories(imu-stream-reader PRIVATE ../../include)
