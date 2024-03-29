//===-- Unittests for memcmp ----------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include <gtest/gtest.h>
#include "../../include/string.h"

TEST(LlvmLibcMemcmpTest, CmpZeroByte) {
  const char *lhs = "ab";
  const char *rhs = "yz";
  EXPECT_EQ(__MACONDO_TEST_NAMESPACE::memcmp(lhs, rhs, 0), 0);
}

TEST(LlvmLibcMemcmpTest, LhsRhsAreTheSame) {
  const char *lhs = "ab";
  const char *rhs = "ab";
  EXPECT_EQ(__MACONDO_TEST_NAMESPACE::memcmp(lhs, rhs, 2), 0);
}

TEST(LlvmLibcMemcmpTest, LhsBeforeRhsLexically) {
  const char *lhs = "ab";
  const char *rhs = "az";
  EXPECT_LT(__MACONDO_TEST_NAMESPACE::memcmp(lhs, rhs, 2), 0);
}

TEST(LlvmLibcMemcmpTest, LhsAfterRhsLexically) {
  const char *lhs = "az";
  const char *rhs = "ab";
  EXPECT_GT(__MACONDO_TEST_NAMESPACE::memcmp(lhs, rhs, 2), 0);
}

TEST(LlvmLibcMemcmpTest, Sweep) {
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
    ASSERT_EQ(__MACONDO_TEST_NAMESPACE::memcmp(lhs, rhs, i), 0);

  reset(lhs);
  reset(rhs);
  for (size_t i = 0; i < K_MAX_SIZE; ++i) {
    rhs[i] = 'z';
    ASSERT_LT(__MACONDO_TEST_NAMESPACE::memcmp(lhs, rhs, K_MAX_SIZE), 0);
    rhs[i] = 'a';
  }
}