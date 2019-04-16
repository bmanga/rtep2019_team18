cmake_minimum_required(VERSION 3.8)


add_executable(gait-analysis main.cpp)

set(Caffe2_DIR "/home/pi/pytorch/torch/share/cmake/Caffe2/")
include_directories("/home/pi/pytorch/torch/include")

#find_package(Caffe2 REQUIRED)
find_package(Torch REQUIRED)
message(STATUS "linking against" "${TORCH_LIBRARIES}")

target_link_libraries(gait-analysis PUBLIC telemetry analysis "${TORCH_LIBRARIES}")

target_include_directories(gait-analysis PRIVATE ../../include)
#target_include_directories(gait-analysis PRIVATE /home/bruno/libtorch/include)

