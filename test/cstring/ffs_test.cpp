#include <gtest/gtest.h>
#include "../../include/strings.h"

TEST(LibcFFsIntTest, Equal) {
    for (int i = 0; i < 1000; i++) {
        EXPECT_EQ(__MACONDO_TEST_NAMESPACE::ffs(i), __builtin_ffs(i));
    }
}

TEST(LibcFFsLongIntTest, Equal) {
    for (long int i = 0; i < 1000; i++) {
        EXPECT_EQ(__MACONDO_TEST_NAMESPACE::ffsl(i), __builtin_ffsl(i));
    }
}

TEST(LibcFFsLongLongIntTest, Equal) {
    for (long long int i = 0; i < 1000; i++) {
        EXPECT_EQ(__MACONDO_TEST_NAMESPACE::ffsll(i), __builtin_ffsll(i));
    }
}