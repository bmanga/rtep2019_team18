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
add_executable(qt-gait-gui
	main.cpp
	Training_mode.cpp
	Training_mode.hpp
	CircleWidget.cpp
	CircleWidget.hpp
	progressbar.cpp
	progressbar.hpp
	intro_window.cpp
	intro_window.hpp
	Level_weight_shifting.cpp
	Level_weight_shifting.hpp
	MainWindow.cpp
	MainWindow.hpp
	WelcomeWindow.cpp
	WelcomeWindow.hpp
	CalibrateWindow.cpp
	CalibrateWindow.hpp
  FinalWindow.cpp
  FinalWindow.hpp
	)
# Use the Widgets module from Qt 5
target_link_libraries(qt-gait-gui Qt5::Widgets Qt5::Charts telemetry)
target_include_directories(qt-gait-gui PRIVATE ../../include .)
