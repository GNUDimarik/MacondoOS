/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2022 Dmitry Adzhiev aka GNUDimarik <dmitry.adjiev@gmail.com>
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