//===-- Unittests for stpcpy ----------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include <gtest/gtest.h>
#include "../../include/string.h"

TEST(LlvmLibcStpCpyTest, EmptySrc) {
  const char *empty = "";
  size_t src_size = __MACONDO_TEST_NAMESPACE::strlen(empty);
  char dest[4] = {'a', 'b', 'c', '\0'};

  char *result = __MACONDO_TEST_NAMESPACE::stpcpy(dest, empty);
  ASSERT_EQ(dest + src_size, result);
  ASSERT_EQ(result[0], '\0');
  ASSERT_STREQ(dest, empty);
}

TEST(LlvmLibcStpCpyTest, EmptyDest) {
  const char *abc = "abc";
  size_t src_size = __MACONDO_TEST_NAMESPACE::strlen(abc);
  char dest[4];

  char *result = __MACONDO_TEST_NAMESPACE::stpcpy(dest, abc);
  ASSERT_EQ(dest + src_size, result);
  ASSERT_EQ(result[0], '\0');
  ASSERT_STREQ(dest, abc);
}

TEST(LlvmLibcStpCpyTest, OffsetDest) {
  const char *abc = "abc";
  size_t src_size = __MACONDO_TEST_NAMESPACE::strlen(abc);
  char dest[7] = {'x', 'y', 'z'};

  char *result = __MACONDO_TEST_NAMESPACE::stpcpy(dest + 3, abc);
  ASSERT_EQ(dest + 3 + src_size, result);
  ASSERT_EQ(result[0], '\0');
  ASSERT_STREQ(dest, "xyzabc");
}