cmake_minimum_required(VERSION 3.8)

add_executable(imu-streamer main.cpp)
target_link_libraries(imu-streamer PRIVATE telemetry imu)
target_include_directories(imu-streamer PRIVATE ../../include)
