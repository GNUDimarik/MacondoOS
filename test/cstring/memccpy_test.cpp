//===-- Unittests for memccpy ---------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include <gtest/gtest.h>
#include <stddef.h> // For size_t.
#include "../../include/string.h"

static void check_memccpy(std::vector<char> dst,
                          const std::vector<char> src, int end,
                          size_t count,
                          const std::vector<char> expected,
                          size_t expectedCopied, bool shouldReturnNull = false) {
    // Making sure we don't overflow buffer.
    ASSERT_GE(dst.size(), count);
    // Making sure memccpy returns dst.
    void *result = __MACONDO_TEST_NAMESPACE::memccpy(dst.data(), src.data(), end, count);

    if (shouldReturnNull) {
        ASSERT_EQ(result, static_cast<void *>(nullptr));
    } else {
        ASSERT_EQ(result, static_cast<void *>(dst.data() + expectedCopied));
    }

    // Expected must be of the same size as dst.
    ASSERT_EQ(dst.size(), expected.size());
    // Expected and dst are the same.
    for (size_t i = 0; i < expected.size(); ++i)
        ASSERT_EQ(expected[i], dst[i]);
}

TEST(LlvmLibcMemccpyTest, UntouchedUnrelatedEnd) {
    std::vector<char> dst = {'a', 'b'};
    const std::vector<char> src = {'x', '\0'};
    const std::vector<char> expected = {'a', 'b'};
    check_memccpy(dst, src, 'z', 0, expected, 0, true);
}

TEST(LlvmLibcMemccpyTest, UntouchedStartsWithEnd) {
    std::vector<char> dst = {'a', 'b'};
    const std::vector<char> src = {'x', '\0'};
    const std::vector<char> expected = {'a', 'b'};
    check_memccpy(dst, src, 'x', 0, expected, 0, true);
}

TEST(LlvmLibcMemccpyTest, CopyOneUnrelatedEnd) {
    std::vector<char> dst = {'a', 'b'};
    const std::vector<char> src = {'x', 'y'};
    const std::vector<char> expected = {'x', 'b'};
    check_memccpy(dst, src, 'z', 1, expected, 1, true);
}

TEST(LlvmLibcMemccpyTest, CopyOneStartsWithEnd) {
    std::vector<char> dst = {'a', 'b'};
    const std::vector<char> src = {'x', 'y'};
    const std::vector<char> expected = {'x', 'b'};
    check_memccpy(dst, src, 'x', 1, expected, 1);
}

TEST(LlvmLibcMemccpyTest, CopyTwoUnrelatedEnd) {
    std::vector<char> dst = {'a', 'b'};
    const std::vector<char> src = {'x', 'y'};
    const std::vector<char> expected = {'x', 'y'};
    check_memccpy(dst, src, 'z', 2, expected, 2, true);
}

TEST(LlvmLibcMemccpyTest, CopyTwoStartsWithEnd) {
    std::vector<char> dst = {'a', 'b'};
    const std::vector<char> src = {'x', 'y'};
    const std::vector<char> expected = {'x', 'b'};
    check_memccpy(dst, src, 'x', 2, expected, 1);
}