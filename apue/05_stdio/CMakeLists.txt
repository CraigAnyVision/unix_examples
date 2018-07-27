cmake_minimum_required(VERSION 3.9)
project(05_stdio)

set(CMAKE_CXX_STANDARD 11)

add_executable(buf buf.c)
add_executable(fgetsfputs fgetsfputs.c)
add_executable(getcharbug getcharbug.c)
add_executable(getcputc getcputc.c)
add_executable(memstr memstr.c)
add_executable(mkstemp mkstemp.c)
add_executable(tempfiles tempfiles.c)
