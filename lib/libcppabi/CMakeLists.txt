cmake_minimum_required(VERSION 3.21)
project(cppabi CXX)

include("${TARGET_PLATFORM}/cmake/build_flags.cmake")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_C_FLAGS} ${PLATFORM_C_FLAGS}")

function(BUILD_LIBCPPABI)
    file(GLOB LIBCPPABI_SRCS "src/*.cc")
    add_library(${PROJECT_NAME} ${LIBCPPABI_SRCS})
    include_directories(${PROJECT_NAME} PUBLIC "../../include")
    set(CMAKE_VERBOSE_MAKEFILE on)
endfunction()

BUILD_LIBCPPABI()
