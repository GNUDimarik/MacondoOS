cmake_minimum_required(VERSION 3.10)
project(MacondoOS)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

set(TARGET_PLATFORM "x86_64")

add_subdirectory(stdlib)
add_subdirectory(test)
add_subdirectory(third_party/googletest)