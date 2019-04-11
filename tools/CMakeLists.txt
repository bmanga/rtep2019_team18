cmake_minimum_required(VERSION 3.8)

project(tools)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(IMUStreamer)
add_subdirectory(IMUStreamReader)
add_subdirectory(MockIMUStreamer)
add_subdirectory(QtIMUDisplay)
add_subdirectory(QtSavedataDisplay)
add_subdirectory(fsrReader)
add_subdirectory(Streamer)