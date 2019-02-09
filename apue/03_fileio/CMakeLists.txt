cmake_minimum_required(VERSION 3.9)
project(03_fileio C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic")

add_executable(fileflags fileflags.c)
add_executable(hole hole.c)
add_executable(mycat2 mycat.c modflags.h)
add_executable(seek seek.c)
