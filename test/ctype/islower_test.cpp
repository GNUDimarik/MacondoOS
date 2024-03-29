//===-- Unittests for islower----------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "../../include/ctype.h"
#include <gtest/gtest.h>

TEST(LlvmLibcIsLower, DefaultLocale) {
  // Loops through all characters, verifying that lowercase letters
  // return a non-zero integer and everything else returns zero.
  for (int ch = 0; ch < 255; ++ch) {
    if ('a' <= ch && ch <= 'z')
      EXPECT_NE(__MACONDO_TEST_NAMESPACE::islower(ch), 0);
    else
      EXPECT_EQ(__MACONDO_TEST_NAMESPACE::islower(ch), 0);
  }
}