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
#ifndef MACONDO_STL_UTILITY_INTERNAL_H
#define MACONDO_STL_UTILITY_INTERNAL_H

#include <internal/stl_base_internal.h>
#include <internal/stl_type_traits_internal.h>
#include <internal/stl_memory_internal.h>

__STD_BEGIN_NAMESPACE

template<typename _Type>
constexpr typename __STD_NAMESPACE::remove_reference<_Type>::type &&
move(_Type &&__t) noexcept
{ return static_cast<typename __STD_NAMESPACE::remove_reference<_Type>::type &&>(__t); }

template<typename _Type>
void swap(_Type &__first, _Type &__second) noexcept
{
    if (__STD_NAMESPACE::addressof(__first) != __STD_NAMESPACE::addressof(__second)) {
        _Type __tmp = __STD_NAMESPACE::move(__first);
        __first = __STD_NAMESPACE::move(__second);
        __second = __STD_NAMESPACE::move(__tmp);
    }
}

__STD_END_NAMESPACE

#endif //MACONDO_STL_UTILITY_INTERNAL_H