set(BINARY libc_test)

include(ExternalProject)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_C_FLAGS}")

ExternalProject_Add(googletest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG main
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=$ENV{EXTERNAL_INSTALL_LOCATION}
)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp *.cc)

set(SOURCES ${TEST_SOURCES})

link_directories($ENV{EXTERNAL_INSTALL_LOCATION}/lib)
add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-DMACONDO_TEST=1 ")
target_include_directories(${BINARY} PUBLIC $ENV{EXTERNAL_INSTALL_LOCATION}/include)
#target_link_directories(${BINARY} PUBLIC $ENV{EXTERNAL_INSTALL_LOCATION}/lib)

target_link_libraries(${BINARY} PUBLIC c gtest pthread)
add_dependencies(${BINARY} googletest)
