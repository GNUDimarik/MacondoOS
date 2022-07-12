#ifndef DEFS_HPP
#define DEFS_HPP

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
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
/**
 * @brief __STD_NAMESPACE macro defined for testing stdlib under linux environment and if __TEST_DRIVEN__ macro is
 * defined it replaces "std" to "debug_std__" (without quotes)
 */
#ifndef __STD_NAMESPACE
    #if defined(__cplusplus)
        #if defined(__TEST_DRIVEN__)
            #define __STD_NAMESPACE debug_std__
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
#define __STD_END_NAMESPACE }
#endif

#endif //DEFS_HPP