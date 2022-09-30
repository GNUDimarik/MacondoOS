//===-- Unittests for iscntrl----------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "../../include/ctype.h"
#include <gtest/gtest.h>

TEST(LlvmLibcIsCntrl, DefaultLocale) {
  // Loops through all characters, verifying that control characters
  // return a non-zero integer, all others return zero.
  for (int ch = 0; ch < 255; ++ch) {
    if ((0 <= ch && ch <= 0x1f /*US*/) || ch == 0x7f /*DEL*/)
      EXPECT_NE(__STD_NAMESPACE::iscntrl(ch), 0);
    else
      EXPECT_EQ(__STD_NAMESPACE::iscntrl(ch), 0);
  }
}