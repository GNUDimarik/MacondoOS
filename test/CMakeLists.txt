set(BINARY libc_test)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

set(SOURCES ${TEST_SOURCES})

add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-g3 -DMACONDO_TEST=1")
target_link_libraries(${BINARY} PUBLIC libc gtest)