cmake_minimum_required(VERSION 3.9)
project(02_standards C)

set(CMAKE_C_STANDARD 99)

add_executable(conf conf.c print_conf.h)
add_executable(options options.c print_conf.h)
