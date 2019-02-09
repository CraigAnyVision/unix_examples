cmake_minimum_required(VERSION 3.9)
project(01_intro C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic")

add_executable(getcputc getcputc.c)
add_executable(hello hello.c)
add_executable(ls1 ls1.c)
add_executable(mycat mycat.c)
add_executable(shell1 shell1.c)
add_executable(shell2 shell2.c)
add_executable(testerror testerror.c)
add_executable(uidgid uidgid.c)
