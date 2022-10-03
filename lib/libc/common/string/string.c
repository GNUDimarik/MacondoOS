#include <string.h>
#include <ctype.h>

/**
 * @brief memcpy - copy length bytes from the object pointed to by src into
 *                 the object pointed to by dest. If copying takes place between
 *                 objects that overlap, the behavior is undefined.
 * @param dest   - pointer to destination
 * @param src    - pointer to source
 * @param length - bytes number to copy
 * @return       - pointer to destination
 *
 * The memcpy() function does not check for the overflow of the receiving
 * memory area.
 */
void *memcpy(void *dest, const void *src, size_t length) {
    unsigned char *d = (unsigned char *) dest;
    unsigned char *s = (unsigned char *) src;

    if (d == s) {
        return d;
    }

    while (length--) {
        *d++ = *s++;
    }

    return dest;
}

/**
 * @brief memmove - copies length bytes from the object pointed to by src into the object
 *                  pointed to by dest.
 * @param dest    - pointer to area to copy to
 * @param src     - pointer to area to copy from
 * @param length  - bytes number to copy
 * @return        - dest
 *
 * Case when src less than dest handles correctly.
 * There is no temporary array inside
 */
void *memmove(void *dest, const void *src, size_t length) {
    unsigned char *d = (unsigned char *) dest;
    unsigned char *s = (unsigned char *) src;

    if (s >= d) {
        /* copy forward */
        while (length-- > 0) {
            *d++ = *s++;
        }
    } else if (s <= d) {
        /* copy backward */
        d += length;
        s += length;

        while (length-- > 0) {
            *--d = *--s;
        }
    }

    return dest;
}

/**
 * @brief  memchr - locate the first occurrence of needle
 *                  (converted to an unsigned char) in the initial count bytes
 *                  (each interpreted as unsigned char) pointed to by memory.
 * @param  memory - memory where we want to search needle
 * @param  needle - characted to search in memory
 * @param  count  - count of bytes for searching
 * @return          pointer to the located byte, or a null pointer
 *                  if the byte is not found.
 */
void *memchr(const void *memory, int needle, size_t count) {
    unsigned char *p = (unsigned char *) memory;

    while (count-- > 0) {
        if (*p++ == (unsigned char) needle) {
            return --p;
        }
    }

    return NULL;
}

void *memrchr(const void *mem, int needle, size_t count) {
    unsigned char *s = (unsigned char *) mem + count - 1;

    while (count-- > 0) {
        if (*s-- == (unsigned char) needle) {
            return ++s;
        }
    }

    return NULL;
}

/**
 * @brief memcmp - compares length bytes (each interpreted as unsigned char)
 *                 the object pointed to by first to the first n bytes of the
 *                 object pointed to by second.
 * @param first  - pointer to first memory area
 * @param second - pointer to second memory area
 * @param length - bytes number to compare
 * @return         -1 if first < second, 1 otherwise and 0 if they are equal
 */
int memcmp(const void *first, const void *second, size_t length) {
    unsigned char *m1 = (unsigned char *) first;
    unsigned char *m2 = (unsigned char *) second;
    size_t i = 0;

    for (i = 0; i < length; i++) {
        if (m1[i] != m2[i]) {
            return m1[i] - m2[i];
        }
    }

    return 0;
}

/**
 * @brief same as memcmp
 * @see memcmp
 */
int bcmp(const void *first, const void *second, size_t length) {
    return memcmp(first, second, length);
}

/**
 * @brief  memset - copies valie (converted to an unsigned char) into each
 *                  of the first length bytes of the object pointed to by dest.
 * @param  dest   - dest to set
 * @param  value  - value to set which
 * @param  length - size of bytes to fill
 * @return          dest; no return value is reserved to indicate an error.
 */
void *memset(void *dest, int value, size_t length) {
    unsigned char *p = (unsigned char *) dest;

    while (length-- > 0) {
        *p++ = (unsigned char) value;
    }

    return dest;
}

/**
 * @brief  strcat - append a copy of the string pointed to by src
 *                  (including the terminating NULL character) to the end of the
 *                  string pointed to by dest.
 * @param  dest   - string to append to
 * @param  src    - string to append which
 * @return        - dest. no return value shall be reserved to indicate an error.
 *
 * The initial byte of src overwrites the NULL character at the end of dest.
 * If copying takes place between objects that overlap, the behavior
 * is undefined.
 */
char *strcat(char *dest, const char *src) {
    char *d = dest;
    const char *s = src;

    while (*d++) {}

    --d;

    while (*s) {
        *d++ = *s++;
    }

    return dest;
}

/**
 * @brief  strncat  - append not more than length bytes (a NULL character and
 *                    bytes that follow it are not appended) from the array
 *                    pointed to by src to the end of the string pointed to by
 *                    dest
 * @param  dest     - string to append to
 * @param  src      - string to append which
 * @return            dest. no return value shall be reserved to indicate an
 *                    error.
 */
char *strncat(char *dest, const char *src, size_t length) {
    char *d = dest;
    const char *s = src;

    while (*d++) {}

    --d;

    while (*s && length-- > 0) {
        *d++ = *s++;
    }

    *d = '\0';
    return dest;
}

/**
 * @brief  strchr - locates the first occurrence of needle (converted to a char)
 *                  in the string pointed to by str. The terminating NULL character
 *                  is considered to be part of the string
 * @param  str    - string to search to
 * @param  needle - character to search which
 * @return          a pointer to the byte, or a null pointer if the byte was
 *                  not found
 */
char *strchr(const char *str, int needle) {
    char *s = (char *) str;

    do {
        if (*s == (char) needle) {
            return s;
        }
    } while (*s++);

    return NULL;
}

/**
 * @brief  strrchr - locates the last occurrence of needle (converted to a char)
 *                   in the string pointed to by str. The terminating NUL
 *                   character is considered to be part of the string.
 * @param  str     - string to search to
 * @param  needle  - character to search which
 * @return           a pointer to the byte or a null pointer if needle does not
 *                   occur in the string.
 */
char *strrchr(const char *str, int needle) {
    const char *s = str;
    long pos = -1;

    do {
        if (*s == needle) {
            pos = s - str;
        }
    } while (*s++);

    return (pos == -1 ? NULL : (char *) str + pos);
}

/**
 * @brief  strcmp - compares the string pointed to by first to the string
 *                  pointed to by second
 * @param  first  - pointer to first string
 * @param  second - pointer to second string
 * @return          -1 if first < second, 1 otherwise and 0 if they are equal
 */
int strcmp(const char *first, const char *second) {
    char *f = (char *) first;
    char *s = (char *) second;

    do {
        if (*f != *s) {
            return *f - *s;
        }
    } while (*f++ && *s++);

    return 0;
}

/**
 * @brief  strncmp - compare not more than len bytes (bytes that follow a NUL
 *         character are not compared) from the array pointed to by first to
 *         the array pointed to by second
 * @param  first   - pointer to first string
 * @param  second  - pointer to second string
 * @param  length  - bytes number to compare
 * @return           -1 if first < second, 1 otherwise and 0 if they are equal
 */
int strncmp(const char *first, const char *second, size_t len) {
    size_t i = 0;

    for (i = 0; i < len; i++) {
        if (first[i] != second[i]) {
            return first[i] - second[i];
        }

        if (first[i] == '\0' || second[i] == '\0') {
            break;
        }
    }

    return 0;
}

/**
 * @brief  strcpy - copies the string pointed to by src (including the
 *                  terminating NULL character) into the array pointed to by dest
 * @param  dest   - destination of copy
 * @param  src    - source of copy
 * @return          a pointer  to dest
 *
 * If copying takes place between objects that overlap, the behavior is undefined
 */
char *strcpy(char *dest, const char *src) {
    char *d = dest;
    char *s = (char *) src;

    do {
        *d = *s;
    } while (*s++ && *d++);

    return dest;
}

/**
 * @brief strncpy - not more than n bytes (bytes that follow a NULL character
 *        are not copied) from the array pointed to by src to the array
 *        pointed to by dest
 *
 * @note If copying takes place between objects that overlap, the behavior is undefined.
 *
 * If the array pointed to by dest is a string that is shorter than n characters, null characters
 * are appended to the copy in the array pointed to by src, until n characters in all have been
 * written
 *
 * @param dest    - destination of copying
 * @param src     - source of copying
 * @param n       - number bytes to copy
 * @return        - a value of dest
 */
char *strncpy(char *dest, const char *src, size_t n) {
    char *d = dest;
    char *s = (char *) src;

    while (n > 0) {
        if (*s != '\0') {
            *d++ = *s++;
        } else {
            *d++ = '\0';
        }

        n--;
    }

    return dest;
}

/**
 * @brief  strspn - computes the length (in bytes) of the maximum initial segment
 *                  of the string pointed to by str which consists entirely
 *                  of bytes from the string pointed to by accept
 * @param  str    - string to check
 * @param  accept - set of accepted characters
 * @return          the computed length; no return value is reserved to indicate
 *                  an error
 */
size_t strspn(const char *str, const char *accept) {
    size_t res = 0;

    while (*str) {

        if (strchr(accept, *str++) == NULL) {
            break;
        }

        res++;
    }

    return res;
}

/**
 * @brief  strlen - compute the number of bytes in the string to which str points,
 *                  not including the terminating NULL character.
 * @param  str    - string to calculate length
 * @return          length of str
 */
size_t strlen(const char *str) {
    size_t res = 0;

    while (*str++ != '\0') {
        res++;
    }

    return res;
}

/**
 * @brief strcspn - compute the length (in bytes) of the maximum initial segment
 *                  of the string pointed to by str which consists entirely of
 *                  bytes not from the string pointed to by reject
 * @param str     - string to check
 * @param reject  - set of rejected characters
 * @return        - index of first occurency of any character from reject or
 *                  NULL if not found no return value is reserved to indicate an
 *                  error.
 */
size_t strcspn(const char *str, const char *reject) {
    const char *s = str;
    size_t res = 0;

    while (*s) {
        if (strchr(reject, *s++) == NULL) {
            res++;
        } else {
            break;
        }
    }

    return res;
}

/**
 * @brief  strpbrk - locate the first occurrence in the string pointed to by str
 *                   of any byte from the string pointed to by accept
 * @param  str     - string to check
 * @param  accept  - set of accepted characters
 * @return         - a pointer to the byte or a null pointer if no byte from str
 *                   occurs in accept
 */
char *strpbrk(const char *str, const char *accept) {
    char *s = (char *) str;

    while (*s) {
        if (strchr(accept, *s++) != NULL) {
            return --s;
        }
    }

    return NULL;
}

/**
 * @brief  strstr   - locate the first occurrence in the string pointed
 *                    to by haystack of the sequence of bytes
 *                    (excluding the terminating null byte) in the string
 *                    pointed to by needle
 * @param  haystack - string to search in
 * @param  needle   - string which needs to be find
 * @return            a pointer to the located string or a null pointer
 *                    if the string is not found
 *
 * If needle points to a string with zero length, the function shall return
 * haystack.
 */
char *strstr(const char *haystack, const char *needle) {
    size_t needle_len = strlen(needle);
    size_t haystack_len = strlen(haystack);
    size_t i = 0;

    if (!needle_len && !haystack_len) {
        return (char *) haystack;
    }

    for (i = haystack_len; i >= needle_len; i--, haystack++) {
        if (strncmp(haystack, needle, needle_len) == 0) {
            return (char *) haystack;
        }
    }

    return NULL;
}

/**
 * @brief  strtok - a sequence of calls to strtok() breaks the string pointed to
 *                  by str into a sequence of tokens, each of which is delimited
 *                  by a byte from the string pointed to by delim
 * @param  str    - string to split
 * @param  delim  - separators
 * @return        - pointer to the first byte of a token. Otherwise, if there
 *                  is no token, strtok() shall return a null pointer.
 *
 * the first call in the sequence has s as its first argument, and is followed
 * by calls with a null pointer as their first argument. The separator string
 * pointed to by sep may be different from call to call.
 *
 * The first call in the sequence searches the string pointed to by str for the
 * first byte that is not contained in the current separator string pointed to
 * by delim. If no such byte is found, then there are no tokens in the string
 * pointed to by str and strtok() shall return a null pointer. If such a byte
 * is found, it is the start of the first token.
 *
 * The strtok() function then searches from there for a byte that is contained
 * in the current separator string. If no such byte is found, the current token
 * extends to the end of the string pointed to by str, and subsequent searches
 * for a token shall return a null pointer. If such a byte is found, it is
 * overwritten by a NULL character, which terminates the current token.
 * The strtok() function saves a pointer to the following byte, from which the
 * next search for a token shall start.
 *
 * Each subsequent call, with a null pointer as the value of the first argument,
 * starts searching from the saved pointer and behaves as described above.
 */
char *strtok(char *str, const char *delim) {
    static char *old_str = NULL;
    return strtok_r(str, delim, &old_str);
}

/**
 * @see strtock
 * @brief strtok_r - is a reentrant version of strtok
 * @param str      - string to split
 * @param delim    - separators
 * @param saveptr  - used internally in order to maintain context between successive calls
 * @return
 */
char *strtok_r(char *str, const char *delim,
               char **saveptr) {
    char *old_str = saveptr ? *saveptr : NULL;
    char *res = NULL;

    if (!str) {
        if (!old_str) {
            return NULL;
        }
    } else {
        old_str = str;
    }

    old_str += strspn(old_str, delim);

    if (*old_str == '\0') {
        return NULL;
    }

    res = old_str++;
    old_str += strcspn(old_str, delim);

    if (*old_str != '\0') {
        *old_str++ = '\0';
    }

    *saveptr = old_str;
    return res;
}

/**
 * @brief memccpy - copies not more than n bytes from src to dest and stop working once coccured
 * @param dest    - destination of the copy
 * @param src     - source of the copy
 * @param c       - stop character
 * @param n       - number of bytest to copy
 * @return
 */
void *memccpy(void *dest, const void *src, int c, size_t n) {
    size_t i;
    unsigned char *d = (unsigned char *) dest;
    const unsigned char *s = (const unsigned char *) src;

    if (n > 0) {
        for (i = 0; i < n; i++) {
            d[i] = s[i];

            if (s[i] == c) {
                return d + i + 1;
            }
        }
    }

    return NULL;
}

/**
 * @brief strrev - reverses input string
 * @param str    - input string to reverse
 * @return       - reversed version of str
 * @note strrev implements inplace algorithm. e.g. it modifies an input string
 */
char *strrev(char *str) {
    size_t len = strlen(str);
    int i, j;
    char c = 0;

    for (i = 0, j = len - 1; i < j; i++, j--) {
        c = str[i];
        str[i] = str[j];
        str[j] = c;
    }

    return str;
}

/**
 * @brief  strupr - is used for converting of string to upper case
 * @param str     - string to be upper cased
 * @return upper cased version of str
 * @note strupr implements inplace algorithm. e.g. it modifies an input string
 */
char *strupr(char *str) {
    char *p = str;

    do {
        *p = toupper(*p);
    } while (*p++ != '\0');

    return str;
}

/**
 * @brief  strlwr - is used for converting of string to lower case
 * @param str     - string to be lower cased
 * @return upper cased version of str
 * @note strlwr implements inplace algorithm. e.g. it modifies an input string
 */
char *strlwr(char *str) {
    char *p = str;

    do {
        *p = tolower(*p);
    } while (*p++ != '\0');

    return str;
}