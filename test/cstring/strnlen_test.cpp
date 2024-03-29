//===-- Unittests for strnlen ---------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include <gtest/gtest.h>
#include <stddef.h>
#include "../../include/string.h"

TEST(LlvmLibcStrNLenTest, EmptyString) {
  const char *empty = "";
  ASSERT_EQ(static_cast<size_t>(0), __MACONDO_TEST_NAMESPACE::strnlen(empty, 0));
  // If N is greater than string length, this should still return 0.
  ASSERT_EQ(static_cast<size_t>(0), __MACONDO_TEST_NAMESPACE::strnlen(empty, 1));
}

TEST(LlvmLibcStrNLenTest, OneCharacterString) {
  const char *single = "X";
  ASSERT_EQ(static_cast<size_t>(1), __MACONDO_TEST_NAMESPACE::strnlen(single, 1));
  // If N is zero, this should return 0.
  ASSERT_EQ(static_cast<size_t>(0), __MACONDO_TEST_NAMESPACE::strnlen(single, 0));
  // If N is greater than string length, this should still return 1.
  ASSERT_EQ(static_cast<size_t>(1), __MACONDO_TEST_NAMESPACE::strnlen(single, 2));
}

TEST(LlvmLibcStrNLenTest, ManyCharacterString) {
  const char *many = "123456789";
  ASSERT_EQ(static_cast<size_t>(9), __MACONDO_TEST_NAMESPACE::strnlen(many, 9));
  // If N is smaller than the string length, it should return N.
  ASSERT_EQ(static_cast<size_t>(3), __MACONDO_TEST_NAMESPACE::strnlen(many, 3));
  // If N is zero, this should return 0.
  ASSERT_EQ(static_cast<size_t>(0), __MACONDO_TEST_NAMESPACE::strnlen(many, 0));
  // If N is greater than the string length, this should still return 9.
  ASSERT_EQ(static_cast<size_t>(9), __MACONDO_TEST_NAMESPACE::strnlen(many, 42));
}

TEST(LlvmLibcStrNLenTest, CharactersAfterNullTerminatorShouldNotBeIncluded) {
  const char str[5] = {'a', 'b', 'c', '\0', 'd'};
  ASSERT_EQ(static_cast<size_t>(3), __MACONDO_TEST_NAMESPACE::strnlen(str, 3));
  // This should only read up to the null terminator.
  ASSERT_EQ(static_cast<size_t>(3), __MACONDO_TEST_NAMESPACE::strnlen(str, 4));
  ASSERT_EQ(static_cast<size_t>(3), __MACONDO_TEST_NAMESPACE::strnlen(str, 5));
}
