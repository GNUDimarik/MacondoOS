//===-- Unittests for strncpy ---------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include <gtest/gtest.h>
#include <stddef.h> // For size_t.
#include "../../include/string.h"
#include <vector>

void check_strncpy(std::vector<char> &dst,
                   const std::vector<char> &src, size_t n,
                   const std::vector<char> &expected) {
    // Making sure we don't overflow buffer.
    ASSERT_GE(dst.size(), n);
    // Making sure strncpy returns dst.
    ASSERT_EQ(__MACONDO_TEST_NAMESPACE::strncpy(dst.data(), src.data(), n), dst.data());
    // Expected must be of the same size as dst.
    ASSERT_EQ(dst.size(), expected.size());
    // Expected and dst are the same.
    for (size_t i = 0; i < expected.size(); ++i)
        ASSERT_EQ(expected[i], dst[i]);
}

TEST(LlvmLibcStrncpyTest, Untouched) {
    std::vector<char> dst = {'a', 'b'};
    std::vector<char> src = {'x', '\0'};
    std::vector<char> expected = {'a', 'b'};
    check_strncpy(dst, src, 0, expected);
}

TEST(LlvmLibcStrncpyTest, CopyOne) {
    std::vector<char> dst = {'a', 'b'};
    std::vector<char> src = {'x', 'y'};
    std::vector<char> expected = {'x', 'b'}; // no \0 is appended
    check_strncpy(dst, src, 1, expected);
}

TEST(LlvmLibcStrncpyTest, CopyNull) {
    std::vector<char> dst = {'a', 'b'};
    std::vector<char> src = {'\0', 'y'};
    std::vector<char> expected = {'\0', 'b'};
    check_strncpy(dst, src, 1, expected);
}

TEST(LlvmLibcStrncpyTest, CopyPastSrc) {
    std::vector<char> dst = {'a', 'b'};
    std::vector<char> src = {'\0', 'y'};
    std::vector<char> expected = {'\0', '\0'};
    check_strncpy(dst, src, 2, expected);
}