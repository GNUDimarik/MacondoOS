set(ENV{COMMON_CXX_FLAGS} "-I$ENV{MACONDO_INCLUDE}/include -std=gnu++20 -O3 -Wall -Wextra -Werror -nostdlib -ffreestanding -fno-exceptions -fno-rtti -mcpu=cortex-a72+nosimd")
set(ENV{COMMON_C_FLAGS} "-I$ENV{MACONDO_INCLUDE}/include -std=gnu18 -O3 -Wall -Wextra -Werror -nostdlib -ffreestanding -mcpu=cortex-a72+nosimd")
