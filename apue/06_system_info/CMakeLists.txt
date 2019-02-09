cmake_minimum_required(VERSION 3.9)
project(06_system_info C)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic")

add_executable(getpwnam getpwnam.c)
add_executable(strftime strftime.c)
add_executable(uname uname.c)
