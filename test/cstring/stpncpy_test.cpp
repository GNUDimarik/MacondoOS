//===-- Unittests for stpncpy ---------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include <gtest/gtest.h>
#include <stddef.h> // For size_t.
#include "../../include/string.h"

static void check_stpncpy(std::vector<char> &dst,
                          const std::vector<char> &src, size_t n,
                          const std::vector<char> &expected,
                          size_t expectedCopied) {
    // Making sure we don't overflow buffer.
    ASSERT_GE(dst.size(), n);
    // Making sure stpncpy returns a pointer to the end of dst.
    ASSERT_EQ(__STD_NAMESPACE::stpncpy(dst.data(), src.data(), n),
              dst.data() + expectedCopied);
    // Expected must be of the same size as dst.
    ASSERT_EQ(dst.size(), expected.size());
    // Expected and dst are the same.
    for (size_t i = 0; i < expected.size(); ++i)
        ASSERT_EQ(expected[i], dst[i]);
}

TEST(LlvmLibcStpncpyTest, Untouched) {
    std::vector<char> dst = {'a', 'b'};
    const std::vector src = {'x', '\0'};
    const std::vector expected = {'a', 'b'};
    check_stpncpy(dst, src, 0, expected, 0);
}

TEST(LlvmLibcStpncpyTest, CopyOne) {
    std::vector<char> dst = {'a', 'b'};
    const std::vector src = {'x', 'y'};
    const std::vector expected = {'x', 'b'}; // no \0 is appended
    check_stpncpy(dst, src, 1, expected, 1);
}

TEST(LlvmLibcStpncpyTest, CopyNull) {
    std::vector<char> dst = {'a', 'b'};
    const std::vector src = {'\0', 'y'};
    const std::vector expected = {'\0', 'b'};
    check_stpncpy(dst, src, 1, expected, 0);
}

TEST(LlvmLibcStpncpyTest, CopyPastSrc) {
    std::vector<char> dst = {'a', 'b'};
    const std::vector src = {'\0', 'y'};
    const std::vector expected = {'\0', '\0'};
    check_stpncpy(dst, src, 2, expected, 0);
}

TEST(LlvmLibcStpncpyTest, CopyTwoNoNull) {
    std::vector<char> dst = {'a', 'b'};
    const std::vector src = {'x', 'y'};
    const std::vector expected = {'x', 'y'};
    check_stpncpy(dst, src, 2, expected, 2);
}

TEST(LlvmLibcStpncpyTest, CopyTwoWithNull) {
    std::vector<char> dst = {'a', 'b'};
    const std::vector src = {'x', '\0'};
    const std::vector expected = {'x', '\0'};
    check_stpncpy(dst, src, 2, expected, 1);
}