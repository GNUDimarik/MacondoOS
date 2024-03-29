/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2024 Dmitry Adzhiev <dmitry.adjiev@gmail.com>
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

#ifndef LINUX_LOG_H
#define LINUX_LOG_H

#ifdef __linux__
#   include <stdio.h>
#       define ALOGD(__ARGS__...)    \
        {                           \
            printf("%s:\t", LOG_TAG); \
            printf(__ARGS__);         \
            printf("\n");             \
        }
#   define ALOGE(__ARGS__...)             \
        {                                    \
            fprintf(stderr, "%s:\t", LOG_TAG); \
            fprintf(stderr, __ARGS__);         \
            fprintf(stderr, "\n");             \
    }
#   endif /* __linux__ */
#endif // LINUX_LOG_H