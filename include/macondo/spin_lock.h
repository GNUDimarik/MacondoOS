/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2023 Dmitry Adzhiev aka GNUDimarik <dmitry.adjiev@gmail.com>
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

#ifndef SPIN_LOCK__SPIN_LOCK_H_
#define SPIN_LOCK__SPIN_LOCK_H_

// Based on "Correctly implementing a spinlock in C++" at https://rigtorp.se/spinlock/

#include <bits/stl_atomic_internal.h>
#include <asm/cpu.h>

namespace macondo {
namespace utils {

template<typename _Type, _Type __lockedState, _Type __unlockedState>
class basic_spin_lock {
 public:
    basic_spin_lock() __NOTHROW: _M_lock(0) {}
    basic_spin_lock(_Type __value) __NOTHROW: _M_lock(__value) {}

    bool try_lock() __NOTHROW {
        return !_M_lock.load(__STD_NAMESPACE::memory_order_relaxed) &&
            !_M_lock.exchange(__lockedState, __STD_NAMESPACE::memory_order_acquire);
    }

    void lock() __NOTHROW {
        for (;;) {
            // Optimistically assume the lock is free on the first try
            if (!_M_lock.compare_exchange_strong(__lockedState, __STD_NAMESPACE::memory_order_acquire)) {
                return;
            }

            // Wait for lock to be released without generating cache misses
            while (_M_lock.load(__STD_NAMESPACE::memory_order_relaxed)) {
                // Issue X86 PAUSE or ARM YIELD instruction to reduce contention between
                // hyper-threads
                cpu_relax();
            }
        }
    }

    void unlock() __NOTHROW {
        _M_lock.store(__unlockedState, std::memory_order_release);
    }
 private:
    __STD_NAMESPACE::internal::atomic<_Type> _M_lock;
};

using spin_lock = basic_spin_lock<bool, true, false>;
} // namespace utils
} // namespace macondo

#endif //SPIN_LOCK__SPIN_LOCK_H_
