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

#ifndef MACONDOOS_INCLUDE_MACONDO_STDIO_H_
#define MACONDOOS_INCLUDE_MACONDO_STDIO_H_

#include "../defs.h"
#include <stdarg.h>
#include <stddef.h>

__BEGIN_DECLS
__MACONDO_TEST_NAMESPACE_BEGIN

int vsnprintf(char *buf, size_t size, const char *fmt, va_list ap);
int snprintf(char *buffer, size_t size, const char *fmt, ...);
int sprintf(char *buffer, const char *fmt, ...);

__MACONDO_TEST_NAMESPACE_END
__END_DECLS

#endif //MACONDOOS_INCLUDE_MACONDO_STDIO_H_
