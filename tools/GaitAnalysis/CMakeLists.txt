cmake_minimum_required(VERSION 3.8)

add_executable(gait-analysis main.cpp)
target_link_libraries(gait-analysis PRIVATE telemetry analysis)
target_include_directories(gait-analysis PRIVATE ../../include)
