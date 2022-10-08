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
#define bcmp(b1, b2, len) memcmp((b1), (b2), (size_t)(len))

/**
 * @brief bzero - just macro for calling memset
 * @see memset
 */
#define bzero(b, len) (memset((b), '\0', (len)), (void) 0)

/**
 * @brief index - just macro for calling strchr
 * @see strchr
 */
#define index(a, b) strchr((a),(b))

/**
 * @brief rindex - just macro for calling strrchr
 */
#define rindex(a, b) strrchr((a),(b))

/**
 * @brief bcopy   - just macro for calling memmove
 * @see memmove
 */
#define bcopy(b1, b2, len) (memmove((b2), (b1), (len)), (void) 0)

/**
 * @brief strlcpy - copies not more than size bytes from src to dest and guaranteed append NUL byte at end
 * @param dst     - destination of copy
 * @param src     - destination copy to
 * @param size    - max size of bytes to copy
 * @return        - length of source
 * @see strncpy
 */
size_t
strlcpy(char *__restrict__ dst, const char *__restrict__ src, size_t size);

/**
 * @brief strlcat -  appends string src to the end of dst. It will append at most dstsize – strlen(dst) – 1 characters.
 *                   It will then NUL-terminate, unless dstsize is 0 or the original dst string was longer than dstsize
 *                   (in practice this should not happen as it means that either dstsize is incorrect or that
 *                   dst is not a proper string).
 * @param dst      - destination buffer
 * @param src      - string to be appended to dst
 * @param dstsize  -  destination buffer size
 * @return the total length of the string it tried to create
 *
 * @see strcat, strncat
 */
size_t strlcat(char *__restrict__ dst, const char *__restrict__ src, size_t dstsize);

/**
 * @brief strcasecmp - function performs a byte-by-byte comparison of the strings first and second, ignoring the case
 *                     of the characters.  It returns an integer less than, equal to, or greater than zero if first is
 *                     found, respectively, to be less than, to match, or be greater than s2.
 * @param first       - first string to compare
 * @param second      - second string to compare
 * @return  an integer less than, equal to, or greater than zero if first is, after ignoring case, found to be less than,
 *          to match, or be greater  than  second,  respectively.
 * @see strcmp
 */
int strcasecmp(const char *first, const char *second);

int strncasecmp(const char *first, const char *second, size_t n);
__END_DECLS
__STD_END_NAMESPACE
/** @} */