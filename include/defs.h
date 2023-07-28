/*
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

#ifndef DEFS_H
#define DEFS_H

#define __macondo__

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#endif

/* To make clang happy */
#ifndef __THROW
    #if defined(__cplusplus)
        #define __THROW noexcept
    #else
        #define __THROW
    #endif
#endif

#define __NOTHROW __THROW

#ifdef __MACONDO_KERNEL__
#define max(a, b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b;       \
})

#define min(a, b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b;       \
})
#endif

#if defined (__cplusplus)
    #define __EXTERN extern "C"
#else
    #define __EXTERN extern
#endif

#ifndef __BEGIN_DECLS
    #if defined (__cplusplus)
        #define __BEGIN_DECLS extern "C" {
    #else
        #define __BEGIN_DECLS
    #endif /* __cplusplus */
#endif /* #ifndef __BEGIN_DECLS */

#ifndef __END_DECLS
    #if defined (__cplusplus)
        #define __END_DECLS }
    #else
        #define __END_DECLS
#endif /* __cplusplus */

#endif /* #ifndef __END_DECLS */

#ifndef __nonnull
#define __nonnull(params) __attribute__ ((__nonnull__ params))
#endif

#ifndef __unused
#define __unused __attribute__ ((unused))
#endif

#ifndef __MACONDO_TEST_NAMESPACE
    #if defined(__cplusplus)
        #if defined(MACONDO_TEST)
            #define __MACONDO_TEST_NAMESPACE macondo_test_ns__
    #else
            #define __MACONDO_TEST_NAMESPACE
        #endif
    #endif
#endif

#ifndef __MACONDO_TEST_NAMESPACE_BEGIN
    #if defined (__cplusplus)
        #define __MACONDO_TEST_NAMESPACE_BEGIN namespace __MACONDO_TEST_NAMESPACE {
    #else
        #define __MACONDO_TEST_NAMESPACE_BEGIN
    #endif
#endif

#ifndef __MACONDO_TEST_NAMESPACE_END
    #if defined (__cplusplus)
        #define __MACONDO_TEST_NAMESPACE_END }
    #else
        #define __MACONDO_TEST_NAMESPACE_END
    #endif
#endif

#if defined(MACONDO_TEST)
#define __USING_MACONDO_TEST_NAMESPACE using namespace __MACONDO_TEST_NAMESPACE;
#else
#define __USING_MACONDO_TEST_NAMESPACE
#endif

/**
 * @brief __STD_NAMESPACE macro defined for testing stdlib under linux environment and if __TEST_DRIVEN__ macro is
 * defined it replaces "std" to "debug_std__" (without quotes)
 */
#ifndef __STD_NAMESPACE
    #if defined(__cplusplus)
        #if defined(MACONDO_TEST)
            #define __STD_NAMESPACE __test_std__
        #else
            #define __STD_NAMESPACE std
        #endif
    #endif
#endif

#ifndef __STD_BEGIN_NAMESPACE
    #if defined (__cplusplus)
        #define __STD_BEGIN_NAMESPACE namespace __STD_NAMESPACE {
    #else
        #define __STD_BEGIN_NAMESPACE
    #endif
#endif

#ifndef __STD_END_NAMESPACE
    #if defined (__cplusplus)
        #define __STD_END_NAMESPACE }
    #else
        #define __STD_END_NAMESPACE
    #endif
#endif

#if !defined(__GNUC__) && !defined(__clang__)
    #error "I really need Itanium compiler"
#endif

#ifndef __CXXABIV1_NAMESPACE
    #define __CXXABIV1_NAMESPACE __cxxabiv1
#endif

#define __CXXABIV1_BEGIN_NAMESPACE namespace __CXXABIV1_NAMESPACE {
#define __CXXABIV1_END_NAMESPACE }

#endif //DEFS_H