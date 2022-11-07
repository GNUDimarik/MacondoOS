//===-- Unittests for toupper----------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "../../include/ctype.h"
#include <gtest/gtest.h>

TEST(LlvmLibcToUpper, DefaultLocale) {
  for (int ch = 0; ch < 255; ++ch) {
    // This follows pattern 'a' - 32 = 'A'.
    if ('a' <= ch && ch <= 'z')
      EXPECT_EQ(__MACONDO_TEST_NAMESPACE::toupper(ch), ch - 32);
    else
      EXPECT_EQ(__MACONDO_TEST_NAMESPACE::toupper(ch), ch);
  }
}