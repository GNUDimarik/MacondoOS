set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES ${SOURCES})

add_library(libstdcpp STATIC ${SOURCES})


if (${TARGET_PLATFORM} STREQUAL "x86_64")
    #-nostdinc
    set(CMAKE_CXX_FLAGS "-D__TEST_DRIVEN__ -std=gnu++2a -O3 -mno-red-zone -mno-mmx -mno-sse2 -mno-sse3 -mno-sse4 -Wall -Wextra -Werror -nostdinc -nostdlib -ffreestanding -fno-exceptions -fno-rtti")
endif()