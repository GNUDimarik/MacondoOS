#include <ctype.h>

inline int toascii(int c) {
    return (c & 0x7f);
}

inline int isascii(int c) {
    return c >= 0 && c <= 127;
}

inline int isalnum(int c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

inline int isalpha(int c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

inline int isblank(int c) {
    return c == 9 || c == 32;
}

inline int iscntrl(int c) {
    return (c >= 0 && c <= 31) || c == 127;
}

inline int isdigit(int c) {
    return c >= '0' && c <= '9';
}

inline int isgraph(int c) {
    return c >= 33 && c <= 126;
}

inline int islower(int c) {
    return c >= 'a' && c <= 'z';
}

inline int isprint(int c) {
    return c >= 32 && c <= 126;
}

inline int ispunct(int c) {
    return (c >= 33 && c <= 47) || (c >= 58 && c <= 64)
        || (c >= 91 && c <= 96) || (c >= 123 && c <= 126);
}

inline int isspace(int c) {
    return (c >= 9 && c <= 13) || c == 32;
}

inline int isupper(int c) {
    return c >= 'A' && c <= 'Z';
}

inline int isxdigit(int c) {
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

inline int tolower(int c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    }

    return c;
}

inline int toupper(int c) {
    if (c >= 'a' && c <= 'z') {
        return c - ('a' - 'A');
    }

    return c;
}