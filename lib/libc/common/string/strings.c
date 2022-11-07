#include <strings.h>
#include <string.h>
#include <ctype.h>

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

int strcasecmp(const char *first, const char *second) {
    char *f = (char *) first;
    char *s = (char *) second;

    do {
        if (tolower(*f) != tolower(*s)) {
            return tolower(*f) - tolower(*s);
        }
    } while (*f++ && *s++);

    return 0;
}

int strncasecmp(const char *first, const char *second, size_t n) {
    size_t i = 0;

    for (i = 0; i < n; i++) {
        if (tolower(first[i]) != tolower(second[i])) {
            return tolower(first[i]) - tolower(second[i]);
        }

        if (first[i] == '\0' || second[i] == '\0') {
            break;
        }
    }

    return 0;
}

int ffs(int val) {
    if (val != 0) {
        int i = 0;
        int shift = 1;

        for (i = 1; shift > 0; i++, shift <<= 1) {
            if (val & shift) {
                return i;
            }
        }
    }

    return 0;
}

int ffsl(long int val) {
    if (val != 0) {
        long int i = 0;
        long int shift = 1;

        for (i = 1; shift > 0; i++, shift <<= 1) {
            if (val & shift) {
                return i;
            }
        }
    }

    return 0;
}

int ffsll(long long int val) {
    if (val != 0) {
        unsigned long long int i = 0;
        unsigned long long int shift = 1;

        for (i = 1; shift > 0; i++, shift <<= 1) {
            if (val & shift) {
                return i;
            }
        }
    }

    return 0;
}