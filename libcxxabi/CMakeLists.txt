cmake_minimum_required(VERSION 3.21)
project(cxxabi CXX)

include("$ENV{MACONDO_CMAKE_INCLUDE}/common_c_cxx_flags.cmake")

function(BUILD_LIBCXXABI)
    file(GLOB LIBCXXABI_SRCS "src/*.cpp")
    set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} $ENV{COMMON_CXX_FLAGS}")
    include_directories(${PROJECT_NAME} PUBLIC $ENV{MACONDO_INCLUDE} $ENV{MACONDO_LIBCXX_INCLUDE})
    add_library(${PROJECT_NAME} ${LIBCXXABI_SRCS})
endfunction()

BUILD_LIBCXXABI()
