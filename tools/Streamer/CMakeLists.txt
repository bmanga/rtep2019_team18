cmake_minimum_required(VERSION 3.8)

add_executable(streamer main.cpp)
target_link_libraries(streamer PRIVATE telemetry imu fsr)
target_include_directories(streamer PRIVATE ../../include)
