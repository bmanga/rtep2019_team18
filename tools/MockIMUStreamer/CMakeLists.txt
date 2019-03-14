cmake_minimum_required(VERSION 3.8)

add_executable(mock-imu-streamer main.cpp)
target_link_libraries(mock-imu-streamer PRIVATE telemetry)
target_include_directories(mock-imu-streamer PRIVATE ../../include)
