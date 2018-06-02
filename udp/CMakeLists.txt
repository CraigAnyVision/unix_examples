cmake_minimum_required(VERSION 3.9)
project(udp C)

set(CMAKE_C_STANDARD 99)

add_executable(server server.c utils.h)
add_executable(client client.c utils.h)
