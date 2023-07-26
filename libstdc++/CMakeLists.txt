cmake_minimum_required(VERSION 3.21)
project(stdc++ CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_CXX_FLAGS}")

function(BUILD_LIBSTDCPP)
    file(GLOB LIBSTDCPP_SRCS "src/*.cpp")
    add_library(${PROJECT_NAME} ${LIBSTDCPP_SRCS})
    include_directories(${PROJECT_NAME} PUBLIC $ENV{MACONDO_INCLUDE})
    set(CMAKE_VERBOSE_MAKEFILE on)
endfunction()

BUILD_LIBSTDCPP()
