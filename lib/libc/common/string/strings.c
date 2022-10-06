#include <strings.h>
#include <string.h>

size_t strlcpy(char *__restrict__ dst, const char *__restrict__ src, size_t size) {
    size_t len = strlen(src);

    if (len + 1 < size) {
        memcpy(dst, src, len + 1);
    } else if (size > 0) {
        memcpy(dst, src, size - 1);
        dst[size - 1] = '\0';
    }

    return len;
}

size_t strlcat(char *__restrict__ dst, const char *__restrict__ src, size_t dstsize) {
    char *d = dst;
    const char *s = src;
    size_t n = dstsize;
    size_t dst_len = 0;

    for (; n > 0 && *d; n--, d++) {}
    dst_len = d - dst;
    n = dstsize - dst_len;

    if (n == 0) {
        return strlen(src) + dst_len;
    }

    while (*s) {
        if (n > 1) {
            *d++ = *s;
            n--;
        }
        s++;
    }

    *d = '\0';
    return dst_len + (s - src);
}