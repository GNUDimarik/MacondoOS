#include <strings.h>
#include <string.h>

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

size_t strlcat(char *dst __unused, const char *src __unused, size_t size __unused) {
#if 0
    size_t dst_len = strlen(dst);
    size_t src_len = strlen(src);
    size_t num = size - dst_len;
    char *d = dst + dst_len;

    if (dst_len > 0 && src_len > 0) {
        d--;
        strncat(d, src, size - dst_len - 1);
        return src_len + dst_len - 1;
    }
#endif
    return 0;
}