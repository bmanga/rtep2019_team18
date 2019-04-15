cmake_minimum_required(VERSION 3.8)


add_executable(gait-analysis main.cpp)


find_package(Torch REQUIRED)

target_link_libraries(gait-analysis PUBLIC telemetry analysis "${TORCH_LIBRARIES}")

target_include_directories(gait-analysis PRIVATE ../../include)
#target_include_directories(gait-analysis PRIVATE /home/bruno/libtorch/include)

