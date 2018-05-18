cmake_minimum_required(VERSION 3.9.1)

project(simpleQt)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_PREFIX_PATH "/opt/qt/5.10.1/gcc_64/")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run MOC automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets REQUIRED)

set(SIMPLEQT_SOURCES simpleQt.cpp)

add_executable(simpleQt ${SIMPLEQT_SOURCES})

target_link_libraries(simpleQt Qt5::Widgets)
