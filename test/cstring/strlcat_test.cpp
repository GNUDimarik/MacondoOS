//===-- Unittests for strlcat ---------------------------------------------===//
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
TEST(LlvmLibcStrlcatTest, TooBig) {
  const char *str = "cd";
  char buf[4]{"ab"};
  EXPECT_EQ(__STD_NAMESPACE::strlcat(buf, str, 3), size_t(4));
  EXPECT_STREQ(buf, "ab");
  EXPECT_EQ(__STD_NAMESPACE::strlcat(buf, str, 4), size_t(4));
  EXPECT_STREQ(buf, "abc");
}

TEST(LlvmLibcStrlcatTest, Smaller) {
  const char *str = "cd";
  char buf[7]{"ab"};

  EXPECT_EQ(__STD_NAMESPACE::strlcat(buf, str, 7), size_t(4));
  EXPECT_STREQ(buf, "abcd");
}

TEST(LlvmLibcStrlcatTest, No0) {
  const char *str = "cd";
  char buf[7]{"ab"};
  EXPECT_EQ(__STD_NAMESPACE::strlcat(buf, str, 1), size_t(3));
  EXPECT_STREQ(buf, "ab");
  EXPECT_EQ(__STD_NAMESPACE::strlcat(buf, str, 2), size_t(4));
  EXPECT_STREQ(buf, "ab");
}
#endif
