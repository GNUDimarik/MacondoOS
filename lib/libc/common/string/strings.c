#include <strings.h>
#include <string.h>

/**
 * @brief bzero - sets n bytes in s to zero
 * @param s     - pointer to region zeroize to
 * @param n     - number of bytes to zeroize
 */
void bzero(void *s, size_t n) {
    memset(s, 0, n);
}

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

void bcopy(const void *src, void *dest, size_t size)
{
    memmove(dest, src, size);
}