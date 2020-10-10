cmake_minimum_required(VERSION 3.10)

project(DZ1)

set(EXEC a.out)

set(CMAKE_C_STANDARD 11)

include_directories(includes)

file(GLOB SOURCES src/*.c)

add_executable(${EXEC} ${SOURCES})

enable_testing()
