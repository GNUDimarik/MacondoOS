/**
 * @ingroup strings
 * @{
 */

#pragma once

#include "defs.h"
#include <stddef.h>


__BEGIN_DECLS
__STD_BEGIN_NAMESPACE

/**
 * @brief bzero - sets n bytes in s to zero
 * @param s     - pointer to region zeroize to
 * @param n     - number of bytes to zeroize
 * @see memset
 */
void bzero(void *s, size_t n);

/**
 * @brief strlcpy - copies not more than size bytes from src to dest and guaranteed append NUL byte at end
 * @param dst     - destination of copy
 * @param src     - destination copy to
 * @param size    - max size of bytes to copy
 * @return        - length of source
 * @see strncpy
 */
size_t strlcpy(char *dst, const char *src, size_t size);

/**
 * @brief bcopy   - copies size bytes from src to dest. src and dest may intersect
 * @param src     - source of copy
 * @param dest    - destination copy to
 * @param size    - number of bytes to copy
 * @see memmove
 */
void bcopy(const void *src, void *dest, size_t size);

__END_DECLS
__STD_END_NAMESPACE
/** @} */