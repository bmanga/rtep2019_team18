cmake_minimum_required(VERSION 3.8)

project(rtep_team18)

set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

add_subdirectory(lib)
add_subdirectory(tools)
add_subdirectory(tests)
