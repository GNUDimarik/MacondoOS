cmake_minimum_required(VERSION 3.10)
project(MacondoOS)

set(CMAKE_CXX_STANDARD 20)

set(ENV{EXTERNAL_INSTALL_LOCATION} ${PROJECT_SOURCE_DIR}/third_party)
set(ENV{MACONDO_INCLUDE} ${PROJECT_SOURCE_DIR}/include)
set(ENV{MACONDO_CLANG_INCLUDE} ${PROJECT_SOURCE_DIR}/clang_15.0.7/include)
set(ENV{MACONDO_CMAKE_INCLUDE} ${PROJECT_SOURCE_DIR}/cmake)

add_subdirectory(lib)
add_subdirectory(libstdc++)

if (ENABLE_TESTS)
    add_subdirectory(test)
endif()
