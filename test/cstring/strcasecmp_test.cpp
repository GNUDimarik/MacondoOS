//===-- Unittests for strcasecmp ----------------------------------------------===//
// This is ported strcmp test from LLVM
//===----------------------------------------------------------------------===//

#include <gtest/gtest.h>
#include "../../include/strings.h"

TEST(LlvmLibcStrCaseCmpTest, EmptyStringsShouldReturnZero) {
    const char *s1 = "";
    const char *s2 = "";
    int result = __MACONDO_TEST_NAMESPACE::strcasecmp(s1, s2);
    ASSERT_EQ(result, 0);

    // Verify operands reversed.
    result = __MACONDO_TEST_NAMESPACE::strcasecmp(s2, s1);
    ASSERT_EQ(result, 0);
}

TEST(LlvmLibcStrCaseCmpTest, EmptyStringShouldNotEqualNonEmptyString) {
    const char *empty = "";
    const char *s2 = "abc";
    int result = __MACONDO_TEST_NAMESPACE::strcasecmp(empty, s2);
    // This should be '\0' - 'a' = -97
    ASSERT_EQ(result, -97);

    // Similar case if empty string is second argument.
    const char *s3 = "123";
    result = __MACONDO_TEST_NAMESPACE::strcasecmp(s3, empty);
    // This should be '1' - '\0' = 49
    ASSERT_EQ(result, 49);
}

TEST(LlvmLibcStrCaseCmpTest, EqualStringsShouldReturnZero) {
    const char *s1 = "aBc";
    const char *s2 = "abc";
    int result = __MACONDO_TEST_NAMESPACE::strcasecmp(s1, s2);
    ASSERT_EQ(result, 0);

    // Verify operands reversed.
    result = __MACONDO_TEST_NAMESPACE::strcasecmp(s2, s1);
    ASSERT_EQ(result, 0);
}

TEST(LlvmLibcStrCaseCmpTest, ShouldReturnResultOfFirstDifference) {
    const char *s1 = "___B42__";
    const char *s2 = "___C55__";
    int result = __MACONDO_TEST_NAMESPACE::strcasecmp(s1, s2);
    // This should return 'B' - 'C' = -1.
    ASSERT_EQ(result, -1);

    // Verify operands reversed.
    result = __MACONDO_TEST_NAMESPACE::strcasecmp(s2, s1);
    // This should return 'C' - 'B' = 1.
    ASSERT_EQ(result, 1);
}

TEST(LlvmLibcStrCaseCmpTest, CapitalizedLetterShouldNotBeEqual) {
    const char *s1 = "ABCD";
    const char *s2 = "abCd";
    int result = __MACONDO_TEST_NAMESPACE::strcasecmp(s1, s2);
    ASSERT_EQ(result, 0);

    // Verify operands reversed.
    result = __MACONDO_TEST_NAMESPACE::strcasecmp(s2, s1);
    ASSERT_EQ(result, 0);
}

TEST(LlvmLibcStrCaseCmpTest, UnequalLengthStringsShouldNotReturnZero) {
    const char *s1 = "ABC";
    const char *s2 = "abcd";
    int result = __MACONDO_TEST_NAMESPACE::strcasecmp(s1, s2);
    // '\0' - 'd' = -100.
    ASSERT_EQ(result, -100);

    // Verify operands reversed.
    result = __MACONDO_TEST_NAMESPACE::strcasecmp(s2, s1);
    // 'd' - '\0' = 100.
    ASSERT_EQ(result, 100);
}

TEST(LlvmLibcStrCaseCmpTest, StringArgumentSwapChangesSign) {
    const char *a = "a";
    const char *b = "B";
    int result = __MACONDO_TEST_NAMESPACE::strcasecmp(b, a);
    // 'b' - 'a' = 1.
    ASSERT_EQ(result, 1);

    result = __MACONDO_TEST_NAMESPACE::strcasecmp(a, b);
    // 'a' - 'b' = -1.
    ASSERT_EQ(result, -1);
}