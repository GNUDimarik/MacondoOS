//===-- Unittests for mempcpy ---------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include <string.hpp>
#include <gtest/gtest.h>

#if 0
// Since this function just calls out to memcpy, and memcpy has its own unit
// tests, it is assumed that memcpy works. These tests are just for the specific
// mempcpy behavior (returning the end of what was copied).
TEST(LlvmLibcMempcpyTest, Simple) {
  const char *src = "12345";
  char dest[10];
  void *result = __STD_NAMESPACE::mempcpy(dest, src, 6);
  ASSERT_EQ(static_cast<char *>(result), dest + 6);
  ASSERT_STREQ(src, dest);
}

TEST(LlvmLibcMempcpyTest, ZeroCount) {
  const char *src = "12345";
  char dest[10];
  void *result = __STD_NAMESPACE::mempcpy(dest, src, 0);
  ASSERT_EQ(static_cast<char *>(result), dest);
}
#endif