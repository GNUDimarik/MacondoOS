#include <strings.h>
#include <string.h>

/**
 * @brief bzero - sets n bytes in s to zero
 * @param s     - pointer to region zeroize to
 * @param n     - number of bytes to zeroize
 * @see memset
 */
void bzero(void *s, size_t n) {
    memset(s, 0, n);
}

/**
 * @brief strlcpy - copies not more than size bytes from src to dest and guaranteed append NUL byte at end
 * @param dst     - destination copy to
 * @param src     - source of copy
 * @param size    - max size of bytes to copy
 * @return        - length of source
 * @see strncpy
 */
size_t strlcpy(char *dst, const char *src, size_t size) {
    size_t len = strlen(src);

    if (len + 1 < size) {
        memcpy(dst, src, len + 1);
    } else if (size > 0) {
        memcpy(dst, src, size - 1);
        dst[size - 1] = '\0';
    }

    return len;
}

/**
 * @brief bcopy   - copies size bytes from src to dest. src and dest may intersect
 * @param src     - source of copy
 * @param dest    - destination copy to
 * @param size    - number of bytes to copy
 * @see memmove
 */
void bcopy(const void *src, void *dest, size_t size)
{
    memmove(dest, src, size);
}