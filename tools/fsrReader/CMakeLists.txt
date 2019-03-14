cmake_minimum_required(VERSION 3.8)

add_executable(fsr-streamer main.cpp)
target_link_libraries(fsr-streamer PRIVATE telemetry imu fsr)
target_include_directories(fsr-streamer PRIVATE ../../include)
