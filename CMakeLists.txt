cmake_minimum_required(VERSION 3.10)
project(MacondoOS)

set(CMAKE_CXX_STANDARD 20)

set(TARGET_PLATFORM "ia32e")

add_subdirectory(third_party/googletest)

include("cmake/common_c_cxx_flags.cmake")
add_subdirectory(lib)
add_subdirectory(libstdc++)
add_subdirectory(test)
