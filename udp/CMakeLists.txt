cmake_minimum_required(VERSION 3.9)
project(01_intro C)

set(CMAKE_C_STANDARD 99)

add_executable(server server.c)
add_executable(client client.c)
