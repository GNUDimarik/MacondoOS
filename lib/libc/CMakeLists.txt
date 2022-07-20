cmake_minimum_required(VERSION 3.21)
project(libc C)

set(CMAKE_C_STANDARD 99)
INCLUDE("${TARGET_PLATFORM}/cmake/build_flags.cmake")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${PLATFORM_C_FLAGS}")

MESSAGE(STATUS ${CMAKE_C_FLAGS})
FILE(GLOB LIBC_SRCS "common/*.c")
add_library(${PROJECT_NAME} ${LIBC_SRCS})
