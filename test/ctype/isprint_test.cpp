//===-- Unittests for isprint----------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "../../include/ctype.h"
#include <gtest/gtest.h>

TEST(LlvmLibcIsPrint, DefaultLocale) {
  for (int ch = 0; ch < 255; ++ch) {
    if (' ' <= ch && ch <= '~') // A-Z, a-z, 0-9, punctuation, space.
      EXPECT_NE(__MACONDO_TEST_NAMESPACE::isprint(ch), 0);
    else
      EXPECT_EQ(__MACONDO_TEST_NAMESPACE::isprint(ch), 0);
  }
}