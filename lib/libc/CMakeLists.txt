cmake_minimum_required(VERSION 3.21)
project(libc C)

include("${TARGET_PLATFORM}/cmake/build_flags.cmake")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_C_FLAGS} ${PLATFORM_C_FLAGS}")

function(BUILD_LIBC)
    file(GLOB LIBC_SRCS "common/string/*.c" "common/*.c" "common/stdio/*.c" "common/stdio/*.cpp")
    add_library(${PROJECT_NAME} ${LIBC_SRCS})
    include_directories(${PROJECT_NAME} PUBLIC "../../include")
    set(CMAKE_VERBOSE_MAKEFILE on)
endfunction()

BUILD_LIBC()
