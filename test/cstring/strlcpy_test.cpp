//===-- Unittests for strlcpy ---------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include <gtest/gtest.h>
#include <stdlib.h>
#include "../../include/string.h"

#if 0
TEST(LlvmLibcStrlcpyTest, TooBig) {
  const char *str = "abc";
  char buf[2];
  EXPECT_EQ(__STD_NAMESPACE::strlcpy(buf, str, 2), size_t(3));
  EXPECT_STREQ(buf, "a");

  EXPECT_EQ(__STD_NAMESPACE::strlcpy(nullptr, str, 0), size_t(3));
}

TEST(LlvmLibcStrlcpyTest, Smaller) {
  const char *str = "abc";
  char buf[7]{"111111"};

  EXPECT_EQ(__STD_NAMESPACE::strlcpy(buf, str, 7), size_t(3));
  EXPECT_STREQ(buf, "abc");
  for (const char *p = buf + 3; p < buf + 7; p++)
    EXPECT_EQ(*p, '\0');
}
#endif
