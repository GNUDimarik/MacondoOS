//===-- Unittests for bcmp ------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include <gtest/gtest.h>
#include "../../include/strings.h"

TEST(LlvmLibcBcmpTest, CmpZeroByte) {
  const char *lhs = "ab";
  const char *rhs = "bc";
  EXPECT_EQ(bcmp(lhs, rhs, 0), 0);
}

TEST(LlvmLibcBcmpTest, LhsRhsAreTheSame) {
  const char *lhs = "ab";
  const char *rhs = "ab";
  EXPECT_EQ(bcmp(lhs, rhs, 2), 0);
}

TEST(LlvmLibcBcmpTest, LhsBeforeRhsLexically) {
  const char *lhs = "ab";
  const char *rhs = "ac";
  EXPECT_NE(bcmp(lhs, rhs, 2), 0);
}

TEST(LlvmLibcBcmpTest, LhsAfterRhsLexically) {
  const char *lhs = "ac";
  const char *rhs = "ab";
  EXPECT_NE(bcmp(lhs, rhs, 2), 0);
}

TEST(LlvmLibcBcmpTest, Sweep) {
  static constexpr size_t K_MAX_SIZE = 1024;
  char lhs[K_MAX_SIZE];
  char rhs[K_MAX_SIZE];

  const auto reset = [](char *const ptr) {
    for (size_t i = 0; i < K_MAX_SIZE; ++i)
      ptr[i] = 'a';
  };

  reset(lhs);
  reset(rhs);
  for (size_t i = 0; i < K_MAX_SIZE; ++i)
    EXPECT_EQ(bcmp(lhs, rhs, i), 0);

  reset(lhs);
  reset(rhs);
  for (size_t i = 0; i < K_MAX_SIZE; ++i) {
    rhs[i] = 'b';
    EXPECT_NE(bcmp(lhs, rhs, K_MAX_SIZE), 0);
    rhs[i] = 'a';
  }
}