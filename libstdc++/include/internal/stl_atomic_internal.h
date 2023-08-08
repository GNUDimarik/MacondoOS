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

#ifndef STL_ATOMIC_INTERNAL_H
#define STL_ATOMIC_INTERNAL_H

#include <internal/stl_base_internal.h>
#include <internal/stl_memory_internal.h>

__STD_BEGIN_NAMESPACE

#if defined(__GNUC__)
#   define ATOMIC_BUILTIN(name) __atomic_##name##_n
#elif defined(__clang__)
#   define ATOMIC_BUILTIN(name) __c11_atomic_##name
#endif

typedef enum memory_order {
    memory_order_relaxed = __ATOMIC_RELAXED,
    memory_order_consume = __ATOMIC_CONSUME,
    memory_order_acquire = __ATOMIC_ACQUIRE,
    memory_order_release = __ATOMIC_RELEASE,
    memory_order_acq_rel = __ATOMIC_ACQ_REL,
    memory_order_seq_cst = __ATOMIC_SEQ_CST
} memory_order;

namespace internal {

template<typename _Type>
class atomic {
 public:
    atomic(_Type __desired)
    __NOTHROW: _M_value(__desired) {}

    atomic(const atomic &)
    __NOTHROW = delete;
    atomic(const atomic &&)
    __NOTHROW = delete;

    _Type load(memory_order __order = memory_order::memory_order_seq_cst) const
    __NOTHROW {
        return ATOMIC_BUILTIN(load)(addressof(_M_value), __order);
    }

    _Type load(memory_order __order = memory_order::memory_order_seq_cst) const volatile
    __NOTHROW {
        return ATOMIC_BUILTIN(load)(addressof(_M_value), __order);
    }

    _Type exchange(_Type __desired, memory_order __order = memory_order::memory_order_seq_cst)
    __NOTHROW {
        return ATOMIC_BUILTIN(_exchange)(addressof(_M_value), __desired, __order);
    }

    _Type exchange(_Type __desired, memory_order __order = memory_order::memory_order_seq_cst) volatile
    __NOTHROW {
        return ATOMIC_BUILTIN(_exchange)(addressof(_M_value), __desired, __order);
    }

    void store(_Type __desired, memory_order __order = memory_order::memory_order_seq_cst)
    __NOTHROW {
        ATOMIC_BUILTIN(store)(addressof(_M_value), __desired, __order);
    }

    bool compare_exchange_strong(_Type &__expected, _Type __desired,
                                 memory_order __success = memory_order::memory_order_seq_cst,
                                 memory_order __failure = memory_order::memory_order_seq_cst)
    __NOTHROW {
#if defined(__GNUC__)
        return ATOMIC_BUILTIN(compare_exchange)(addressof(_M_value),
                                                addressof(__expected),
                                                __desired,
                                                false,
                                                __success,
                                                __failure);
#elif defined(__clang__)
        return ATOMIC_BUILTIN(exchange)(addressof(_M_value),
                                        addressof(__expected),
                                        __desired,
                                        __success,
                                        __failure);
#endif
    }
 private:
    _Type _M_value;
};
} // namespace internal

__STD_END_NAMESPACE

#endif // STL_ATOMIC_INTERNAL_H