/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2023 Dmitry Adzhiev <dmitry.adjiev@gmail.com>
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

#include <bits/stl_atomic_internal.h>
#include <asm/cpu.h>

/**
 * @defgroup libcxx_abi itanium c++ ABI
 * This file contains implementation of guards from Itanium C++ ABI from here
 * https://itanium-cxx-abi.github.io/cxx-abi/abi.html
 */

#define __XCA_UINT_64_TYPE__ __UINT64_TYPE__
/**
 * On big-endian 64-bit platforms, the guard word is a single 64-bit atomic
 * with the lock in the low bit and the initialised bit in the highest
 * byte.
 */

#ifdef __aarch64__
#define __XCA_AARCH64_LOCKED_BIT 0UL
#else
#define __XCA_AARCH64_LOCKED_BIT 63UL
#endif

#ifdef __aarch64__
#define __XCA_AARCH64_INIT_BIT 56UL
#else /* Testing only */
#define __XCA_AARCH64_INIT_BIT 0UL
#endif

#define __XCA_AARCH64_LOCK_LOCKED_STATE (1UL << __XCA_AARCH64_LOCKED_BIT)
#define __XCA_AARCH64_LOCK_INITIALIZED_STATE (1UL << __XCA_AARCH64_INIT_BIT)

#define __XCA_LOCK_STATE_DONE  0
#define __XCA_LOCK_STATE_SUCCEEDED 1
#define __XCA_LOCK_STATUS_FAILED 2

namespace {

using __STD_NAMESPACE::memory_order;

struct __xca_guard {
    __STD_NAMESPACE::internal::atomic<__XCA_UINT_64_TYPE__> __M_value;

    void _M_unlock(bool __is_initialized)
    __NOTHROW {
        __M_value
            .store(__is_initialized ? __XCA_AARCH64_LOCK_INITIALIZED_STATE : 0, memory_order::memory_order_release);
    }

    bool _M_is_initialized() const __THROW {
        return (__M_value.load(memory_order::memory_order_acquire) & __XCA_AARCH64_LOCK_INITIALIZED_STATE)
            == __XCA_AARCH64_LOCK_INITIALIZED_STATE;
    }

    int _M_try_lock() __NOTHROW {
        __XCA_UINT_64_TYPE__ __prev = 0;

        if (__M_value.compare_exchange_strong(__prev, __XCA_AARCH64_LOCK_LOCKED_STATE)) {
            return __XCA_LOCK_STATE_SUCCEEDED;
        }

        if (__prev == __XCA_AARCH64_LOCK_INITIALIZED_STATE) {
            return __XCA_LOCK_STATE_DONE;
        }

        return __XCA_LOCK_STATUS_FAILED;
    }
};
} // unnamed namespace

__CXXABIV1_BEGIN_NAMESPACE
__BEGIN_DECLS

/**
 * @ingroup libcxx_abi
 * @brief __cxa_guard_acquire calls by compiler during static stuff initialization
 * @param __guard compiler's lock
 *
 * Returns 1 if the initialization is not yet complete; 0 otherwise. This function is called before initialization
 * takes place. If this function returns 1, either __cxa_guard_release or __cxa_guard_abort must be called with the
 * same argument. The first byte of the guard_object is not modified by this function.
 */

int __cxa_guard_acquire(__xca_guard *__guard) __THROW {
    if (__guard->_M_is_initialized()) {
        return __XCA_LOCK_STATE_DONE;
    }

    for (;;) {
        switch (__guard->_M_try_lock()) {
            case __XCA_LOCK_STATE_SUCCEEDED:return __XCA_LOCK_STATE_SUCCEEDED;

            case __XCA_LOCK_STATE_DONE:return __XCA_LOCK_STATE_DONE;

            default:break;
        }

        __cpu_relax();
    }
}

/**
 * @ingroup libcxx_abi
 * @brief __cxa_guard_abort calls by compiler when static stuff initialization is aborted for example by exception
 * @param __guard compiler's lock
 *
 * Compiler may do something like here, his is quote from Itanium C++ ABI:
 *
 * @code
 *    if (obj_guard.first_byte == 0) {
 *        if ( __cxa_guard_acquire (&obj_guard) ) {
 *            try {
 *                ... initialize the object ...;
 *            } catch (...) {
 *                __cxa_guard_abort (&obj_guard);
 *                throw;
 *        }
 *          ... queue object destructor with __cxa_atexit() ...;
 *          __cxa_guard_release (&obj_guard);
 *        }
 *    }
 * @endcode
 */
void __cxa_guard_abort(__xca_guard *__guard) {
    __guard->_M_unlock(false);
}

/**
 * @ingroup libcxx_abi
 * @brief __cxa_guard_abort calls by compiler when static stuff is successfully initialized
 * @param __guard compiler's lock
 */
void __cxa_guard_release(__xca_guard *__guard) {
    __guard->_M_unlock(true);
}

__END_DECLS
__CXXABIV1_END_NAMESPACE

