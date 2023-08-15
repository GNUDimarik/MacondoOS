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

#ifndef MACONDO_TYPE_TRAITS_INTERNAL_H
#define MACONDO_TYPE_TRAITS_INTERNAL_H

#include <internal/stl_base_internal.h>

__STD_BEGIN_NAMESPACE

template<typename _Type, _Type __v>
struct integral_constant
{
    static constexpr _Type value = __v;
    using value_type = _Type;
    using type = integral_constant; // using injected-typename-name
    constexpr operator value_type() const noexcept
    { return value; }
    constexpr value_type operator()() const noexcept
    { return value; } // since c++14
};

using true_type = __STD_NAMESPACE::integral_constant<bool, true>;
using false_type = __STD_NAMESPACE::integral_constant<bool, false>;

template<typename _Type>
struct remove_reference
{
    typedef _Type type;
};
template<typename _Type>
struct remove_reference<_Type &>
{
    typedef _Type type;
};
template<typename _Type>
struct remove_reference<_Type &&>
{
    typedef _Type type;
};

template<typename _Type>
struct remove_cv
{
    typedef _Type type;
};
template<typename _Type>
struct remove_cv<const _Type>
{
    typedef _Type type;
};
template<typename _Type>
struct remove_cv<volatile _Type>
{
    typedef _Type type;
};
template<typename _Type>
struct remove_cv<const volatile _Type>
{
    typedef _Type type;
};

template<typename _Type>
struct remove_const
{
    typedef _Type type;
};
template<typename _Type>
struct remove_const<const _Type>
{
    typedef _Type type;
};

template<typename _Type>
struct remove_volatile
{
    typedef _Type type;
};
template<typename _Type>
struct remove_volatile<volatile _Type>
{
    typedef _Type type;
};

template<typename _Type>
struct is_array
    : public integral_constant<bool, __is_array(_Type)>
{
};

template<typename _Type>
struct is_const
    : public integral_constant<bool, __is_const(_Type)>
{
};

template<typename _Type>
struct is_class
    : public integral_constant<bool, __is_class(_Type)>
{
};

template<typename _Type>
struct is_empty
    : public integral_constant<bool, __is_empty(_Type)>
{
};

template<typename _Type>
struct is_object
    : public integral_constant<bool, __is_object(_Type)>
{
};

template<typename _Type>
struct is_union
    : public integral_constant<bool, __is_union(_Type)>
{
};

template<typename _First, typename _Second>
struct is_same
    : public integral_constant<bool, __is_same(_First, _Second)>
{
};

template<typename _Type>
using remove_reference_t = typename remove_reference<_Type>::type;
template<typename _Type>
using remove_cv_t = typename remove_cv<_Type>::type;
template<typename _Type>
using remove_const_t = typename remove_const<_Type>::type;
template<typename _Type>
using remove_volatile_t = typename remove_volatile<_Type>::type;

template<typename _Type>
inline constexpr bool is_array_v = is_array<_Type>::value;

template<typename _Type>
inline constexpr bool is_const_v = is_const<_Type>::value;

template<typename _Type>
inline constexpr bool is_class_v = is_class<_Type>::value;

template<typename _Type>
inline constexpr bool is_empty_v = is_empty<_Type>::value;

template<typename _Type>
inline constexpr bool is_union_v = is_union<_Type>::value;

template<typename _First, typename _Second>
inline constexpr bool is_same_v = is_same<_First, _Second>::value;

template<typename _Type>
inline constexpr bool is_object_v = is_object<_Type>::value;

__STD_END_NAMESPACE

#endif //MACONDO_TYPE_TRAITS_INTERNAL_H