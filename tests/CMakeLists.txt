cmake_minimum_required(VERSION 3.8)
project(tests)

set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)
find_package(Catch2 REQUIRED)

add_executable(tests
	main.cpp
	dummy.cpp
  )
target_link_libraries(tests PRIVATE Catch2::Catch2)