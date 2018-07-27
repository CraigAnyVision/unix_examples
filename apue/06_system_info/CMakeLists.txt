cmake_minimum_required(VERSION 3.9)
project(06_system_info)

set(CMAKE_CXX_STANDARD 11)

add_executable(getpwnam getpwnam.c)
add_executable(strftime strftime.c)
add_executable(uname uname.c)
