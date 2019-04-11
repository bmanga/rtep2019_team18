cmake_minimum_required(VERSION 3.8)

find_package(fmt REQUIRED)
add_executable(imu-streamer main.cpp)
target_link_libraries(imu-streamer PRIVATE telemetry imu fmt::fmt)
target_include_directories(imu-streamer PRIVATE ../../include)
