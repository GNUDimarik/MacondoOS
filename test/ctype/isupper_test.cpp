//===-- Unittests for isupper----------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "../../include/ctype.h"
#include <gtest/gtest.h>

TEST(LlvmLibcIsUpper, DefaultLocale) {
  // Loops through all characters, verifying that uppercase letters
  // return a non-zero integer and everything else returns zero.
  for (int ch = 0; ch < 255; ++ch) {
    if ('A' <= ch && ch <= 'Z')
      EXPECT_NE(__MACONDO_TEST_NAMESPACE::isupper(ch), 0);
    else
      EXPECT_EQ(__MACONDO_TEST_NAMESPACE::isupper(ch), 0);
  }
}