//===-- Unittests for strdup ----------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "../../include/string.hpp"
#include <gtest/gtest.h>
#include <stdlib.h>

#if 0
TEST(LlvmLibcStrDupTest, EmptyString) {
  const char *empty = "";

  char *result = __STD_NAMESPACE::strdup(empty);
  ASSERT_NE(result, static_cast<char *>(nullptr));
  ASSERT_NE(empty, const_cast<const char *>(result));
  ASSERT_STREQ(empty, result);
  ::free(result);
}

TEST(LlvmLibcStrDupTest, AnyString) {
  const char *abc = "abc";

  char *result = __STD_NAMESPACE::strdup(abc);

  ASSERT_NE(result, static_cast<char *>(nullptr));
  ASSERT_NE(abc, const_cast<const char *>(result));
  ASSERT_STREQ(abc, result);
  ::free(result);
}

TEST(LlvmLibcStrDupTest, NullPtr) {

  char *result = __STD_NAMESPACE::strdup(nullptr);

  ASSERT_EQ(result, static_cast<char *>(nullptr));
}
#endif