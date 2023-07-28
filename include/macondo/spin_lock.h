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

#ifndef SPIN_LOCK__SPIN_LOCK_H_
#define SPIN_LOCK__SPIN_LOCK_H_

// Based on "Correctly implementing a spinlock in C++" at https://rigtorp.se/spinlock/

#include <bits/stl_atomic_internal.h>
#include <asm/cpu.h>


/**
  * @defgroup kernel_library kernel library
 */

/**
 * @ingroup  kernel_library
 * @namespace macondo
 * @brief here is declared some os specific stuff such as spin locks etc
 */
namespace macondo {

/**
 * @ingroup  kernel_library
 * @namespace macondo::utils
 * @brief utils contains os specific utils such as spin lock and other routine stuff
 */
namespace utils {

/**
 * @ingroup  kernel_library
 * @class macondo::utils::basic_spin_lock
 * @ingroup  kernel_library
 * @brief basic_spin_loc template for implementation spin locks
 * @tparam _Type type of spin lock such as uint64_t or bool
 * @tparam __lockedState locked state value
 * @tparam __unlockedState unlocked state value
 *
 * @example
 * basic_spin_lock<bool, true, false>
 *
 * where spin lock type is bool and locked state value is <b>true</b> and <b>false</b>
 */
template<typename _Type, _Type __lockedState, _Type __unlockedState>
class basic_spin_lock {
 public:
    basic_spin_lock() __THROW = default;

    explicit basic_spin_lock(_Type __value)
    __NOTHROW: _M_lock(__value) {}

    bool try_lock()
    __NOTHROW {
        return _M_lock.load(__STD_NAMESPACE::memory_order_relaxed) == __unlockedState &&
            _M_lock.exchange(__lockedState, __STD_NAMESPACE::memory_order_acquire) == __unlockedState;
    }

    void lock()
    __NOTHROW {
        for (;;) {
            if (_M_lock.compare_exchange_strong(__lockedState, __STD_NAMESPACE::memory_order_acquire)
                != __lockedState) {
                return;
            }

            while (_M_lock.load(__STD_NAMESPACE::memory_order_relaxed) != __unlockedState) {
                __cpu_relax();
            }
        }
    }

    bool is_locked() const
    __THROW {
        return _M_lock.load(__STD_NAMESPACE::memory_order_relaxed) == __lockedState;
    }

    void unlock()
    __NOTHROW {
        _M_lock.store(__unlockedState, std::memory_order_release);
    }
 private:
    __STD_NAMESPACE::internal::atomic<_Type> _M_lock;
};

using spin_lock = basic_spin_lock<bool, true, false>;
} // namespace utils
} // namespace macondo

#endif //SPIN_LOCK__SPIN_LOCK_H_
