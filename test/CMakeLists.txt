set(BINARY libstdcpp_test)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

set(SOURCES ${TEST_SOURCES})

add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-g3 -D__TEST_DRIVEN__")
target_link_libraries(${BINARY} PUBLIC /home/dmitry/work/osdev/MacondoOS/build/stdlib/libstdcpp.a gtest)