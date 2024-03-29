/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2022 Dmitry Adzhiev <dmitry.adjiev@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#pragma once

#include "defs.h"
#include <stddef.h>
#include <string.h>

__MACONDO_TEST_NAMESPACE_BEGIN
__BEGIN_DECLS

/**
 * @ingroup strings
 * @{
 */

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

/**
 * @brief strncasecmp - function performs a byte-by-byte comparison of the strings first and second, ignoring the case
 *                      of the characters.  It returns an integer less than, equal to, or greater than zero if first is
 *                      found, respectively, to be less than, to match, or be greater than second
 * @param first       - first string to compare
 * @param second      - second string to compare
 * @param n           - number of characters to compare
 * @return  an integer less than, equal to, or greater than zero if first is, after ignoring case, found to be less than,
 *          to match, or be greater  than  second,  respectively.
 */
int strncasecmp(const char *first, const char *second, size_t n);

/**
 * @brief  ffs - find first set bit
 * @param val  - integer number
 * @return the position of the first (least significant) bit set in the number i
 */
int ffs(int val);

/**
 * @brief ffsl - find first set bit
 * @param val  - long number
 * @return the position of the first (least significant) bit set in the number i
 */
int ffsl(long int val);

/**
 * @brief ffsll - find first set bit
 * @param val   - long long number
 * @return the position of the first (least significant) bit set in the number i
 */
int ffsll(long long int val);

__END_DECLS
__MACONDO_TEST_NAMESPACE_END
/** @} */