cmake_minimum_required(VERSION 3.9)
project(alp_server C)

set(CMAKE_C_STANDARD 99)

add_executable(alp_server main.c server.h common.c module.c server.c time.c issue.c diskfree.c processes.c)
