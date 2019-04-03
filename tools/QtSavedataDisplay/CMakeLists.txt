cmake_minimum_required(VERSION 3.1.0)


# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Charts CONFIG REQUIRED)

# Populate a CMake variable with the sources


# Tell CMake to create the helloworld executable
add_executable(qt-data-visualizer
	chart.cpp
	chart.h
	main_window.cpp
	main_window.h
	chart_view.cpp
	chart_view.h
	main.cpp
	)
# Use the Widgets module from Qt 5
target_link_libraries(qt-data-visualizer Qt5::Widgets Qt5::Charts)
target_include_directories(qt-data-visualizer PRIVATE ../../include .)
