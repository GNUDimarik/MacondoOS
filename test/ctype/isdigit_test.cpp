//===-- Unittests for isdigit----------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "../../include/ctype.h"

#include <gtest/gtest.h>

TEST(LlvmLibcIsDigit, DefaultLocale) {
  // Loops through all characters, verifying that numbers return a
  // non-zero integer and everything else returns zero.
  for (int ch = 0; ch < 255; ++ch) {
    if ('0' <= ch && ch <= '9')
      EXPECT_NE(__MACONDO_TEST_NAMESPACE::isdigit(ch), 0);
    else
      EXPECT_EQ(__MACONDO_TEST_NAMESPACE::isdigit(ch), 0);
  }
}