//===-- Unittests for strncasecmp ----------------------------------------------===//
// This is ported strncasecmp test from LLVM
//===----------------------------------------------------------------------===//

#include <gtest/gtest.h>
#include "../../include/strings.h"

// This group is just copies of the strcmp tests, since all the same cases still
// need to be tested.

TEST(LlvmLibcStrnCaseCmpTest, EmptyStringsShouldReturnZeroWithSufficientLength) {
    const char *s1 = "";
    const char *s2 = "";
    int result = __MACONDO_TEST_NAMESPACE::strncasecmp(s1, s2, 1);
    ASSERT_EQ(result, 0);

    // Verify operands reversed.
    result = __MACONDO_TEST_NAMESPACE::strncasecmp(s2, s1, 1);
    ASSERT_EQ(result, 0);
}

TEST(LlvmLibcStrnCaseCmpTest,
     EmptyStringShouldNotEqualNonEmptyStringWithSufficientLength) {
    const char *empty = "";
    const char *s2 = "abc";
    int result = __MACONDO_TEST_NAMESPACE::strncasecmp(empty, s2, 3);
    // This should be '\0' - 'a' = -97
    ASSERT_EQ(result, -97);

    // Similar case if empty string is second argument.
    const char *s3 = "123";
    result = __MACONDO_TEST_NAMESPACE::strncasecmp(s3, empty, 3);
    // This should be '1' - '\0' = 49
    ASSERT_EQ(result, 49);
}

TEST(LlvmLibcStrnCaseCmpTest, EqualStringsShouldReturnZeroWithSufficientLength) {
    const char *s1 = "aBc";
    const char *s2 = "AbC";
    int result = __MACONDO_TEST_NAMESPACE::strncasecmp(s1, s2, 3);
    ASSERT_EQ(result, 0);

    // Verify operands reversed.
    result = __MACONDO_TEST_NAMESPACE::strncasecmp(s2, s1, 3);
    ASSERT_EQ(result, 0);
}

TEST(LlvmLibcStrnCaseCmpTest,
     ShouldReturnResultOfFirstDifferenceWithSufficientLength) {
    const char *s1 = "___B42__";
    const char *s2 = "___C55__";
    int result = __MACONDO_TEST_NAMESPACE::strncasecmp(s1, s2, 8);
    // This should return 'B' - 'C' = -1.
    ASSERT_EQ(result, -1);

    // Verify operands reversed.
    result = __MACONDO_TEST_NAMESPACE::strncasecmp(s2, s1, 8);
    // This should return 'C' - 'B' = 1.
    ASSERT_EQ(result, 1);
}

TEST(LlvmLibcStrnCaseCmpTest,
     CapitalizedLetterShouldNotBeEqualWithSufficientLength) {
    const char *s1 = "AbCd";
    const char *s2 = "aBcD";
    int result = __MACONDO_TEST_NAMESPACE::strncasecmp(s1, s2, 4);
    ASSERT_EQ(result, 0);

    // Verify operands reversed.
    result = __MACONDO_TEST_NAMESPACE::strncasecmp(s2, s1, 4);
    ASSERT_EQ(result, 0);
}

TEST(LlvmLibcStrnCaseCmpTest,
     UnequalLengthStringsShouldNotReturnZeroWithSufficientLength) {
    const char *s1 = "aBc";
    const char *s2 = "AbcD";
    int result = __MACONDO_TEST_NAMESPACE::strncasecmp(s1, s2, 4);
    // '\0' - 'd' = -100.
    ASSERT_EQ(result, -100);

    // Verify operands reversed.
    result = __MACONDO_TEST_NAMESPACE::strncasecmp(s2, s1, 4);
    // 'd' - '\0' = 100.
    ASSERT_EQ(result, 100);
}