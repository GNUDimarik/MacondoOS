cmake_minimum_required(VERSION 3.10)
project(MacondoOS)

set(CMAKE_CXX_STANDARD 20)

set(TARGET_PLATFORM "ia32e")

include("cmake/common_c_cxx_flags.cmake")

set(CMAKE_CXX_FLAGS ${COMMON_CXX_FLAGS})
set(CMAKE_C_FLAGS   ${COMMON_C_FLAGS})

add_subdirectory(lib)
add_subdirectory(test)
add_subdirectory(third_party/googletest)
