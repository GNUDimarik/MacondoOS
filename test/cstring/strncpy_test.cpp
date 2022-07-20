//===-- Unittests for strncpy ---------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "../../include/string.hpp"
#include <gtest/gtest.h>
#include <stddef.h> // For size_t.

#if 0
class LlvmLibcStrncpyTest : public __STD_NAMESPACE::testing::Test {
public:
  void check_strncpy(__STD_NAMESPACE::cpp::MutableArrayRef<char> dst,
                     const __STD_NAMESPACE::cpp::ArrayRef<char> src, size_t n,
                     const __STD_NAMESPACE::cpp::ArrayRef<char> expected) {
    // Making sure we don't overflow buffer.
    ASSERT_GE(dst.size(), n);
    // Making sure strncpy returns dst.
    ASSERT_EQ(__STD_NAMESPACE::strncpy(dst.data(), src.data(), n), dst.data());
    // Expected must be of the same size as dst.
    ASSERT_EQ(dst.size(), expected.size());
    // Expected and dst are the same.
    for (size_t i = 0; i < expected.size(); ++i)
      ASSERT_EQ(expected[i], dst[i]);
  }
};

TEST_F(LlvmLibcStrncpyTest, Untouched) {
  char dst[] = {'a', 'b'};
  const char src[] = {'x', '\0'};
  const char expected[] = {'a', 'b'};
  check_strncpy(dst, src, 0, expected);
}

TEST_F(LlvmLibcStrncpyTest, CopyOne) {
  char dst[] = {'a', 'b'};
  const char src[] = {'x', 'y'};
  const char expected[] = {'x', 'b'}; // no \0 is appended
  check_strncpy(dst, src, 1, expected);
}

TEST_F(LlvmLibcStrncpyTest, CopyNull) {
  char dst[] = {'a', 'b'};
  const char src[] = {'\0', 'y'};
  const char expected[] = {'\0', 'b'};
  check_strncpy(dst, src, 1, expected);
}

TEST_F(LlvmLibcStrncpyTest, CopyPastSrc) {
  char dst[] = {'a', 'b'};
  const char src[] = {'\0', 'y'};
  const char expected[] = {'\0', '\0'};
  check_strncpy(dst, src, 2, expected);
}
#endif