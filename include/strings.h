/**
 * @ingroup strings
 * @{
 */

#pragma once

#include "defs.h"
#include <stddef.h>
#include <string.h>


__BEGIN_DECLS
__STD_BEGIN_NAMESPACE

/**
 * @brief bcmp  - just macro for calling memcmp
 * @see memcmp
 */
#define bcmp(b1,b2,len) memcmp((b1), (b2), (size_t)(len))

/**
 * @brief bzero - just macro for calling memset
 * @see memset
 */
#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)

/**
 * @brief index - just macro for calling strchr
 * @see strchr
 */
#define index(a,b) strchr((a),(b))

/**
 * @brief rindex - just macro for calling strrchr
 */
#define rindex(a,b) strrchr((a),(b))

/**
 * @brief bcopy   - just macro for calling memmove
 * @see memmove
 */
#define bcopy(b1,b2,len) (memmove((b2), (b1), (len)), (void) 0)

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
 * @brief
 * @param dst
 * @param src
 * @param size
 * @return
 */
size_t strlcat(char *dst, const char *src, size_t size);

__END_DECLS
__STD_END_NAMESPACE
/** @} */