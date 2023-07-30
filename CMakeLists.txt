cmake_minimum_required(VERSION 3.10)
project(MacondoOS)

set(CMAKE_CXX_STANDARD 20)

set(ENV{EXTERNAL_INSTALL_LOCATION} ${PROJECT_SOURCE_DIR}/third_party)
set(ENV{MACONDO_INCLUDE} ${PROJECT_SOURCE_DIR}/include)
set(ENV{MACONDO_CMAKE_INCLUDE} ${PROJECT_SOURCE_DIR}/cmake)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(ENV{MACONDO_COMPILER_INCLUDE} ${PROJECT_SOURCE_DIR}/clang_17.0.0/include)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(ENV{MACONDO_COMPILER_INCLUDE} ${PROJECT_SOURCE_DIR}/gcc_14.0.0/include/)
endif()

add_subdirectory(lib)
add_subdirectory(libstdc++)

if (ENABLE_TESTS)
    add_subdirectory(test)
endif()
