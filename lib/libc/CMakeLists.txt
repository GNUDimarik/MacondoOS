cmake_minimum_required(VERSION 3.21)
project(c C)

include("$ENV{MACONDO_CMAKE_INCLUDE}/common_c_cxx_flags.cmake")

function(BUILD_LIBC)
    file(GLOB LIBC_SRCS "common/string/*.c" "common/*.c" "common/stdio/*.c" "common/stdio/*.cpp")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} $ENV{COMMON_C_FLAGS}")
    include_directories(${PROJECT_NAME} PUBLIC $ENV{MACONDO_INCLUDE})
    add_library(${PROJECT_NAME} ${LIBC_SRCS})
endfunction()

BUILD_LIBC()
