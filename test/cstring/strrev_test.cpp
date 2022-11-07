#include <gtest/gtest.h>
#include "../../include/string.h"

TEST(LibcStrrevTest, EmptyString) {
    char empty[] = {""};

    char *result = __MACONDO_TEST_NAMESPACE::strrev(empty);
    ASSERT_NE(result, static_cast<char *>(nullptr));
    ASSERT_EQ(empty, const_cast<const char *>(result));
    ASSERT_STREQ(empty, result);
}

TEST(LibcStrrevTest, TextString) {
    char array[] = {"Hello World!"};
    char out_array[] = {"!dlroW olleH"};

    char *result = __MACONDO_TEST_NAMESPACE::strrev(array);
    ASSERT_NE(result, static_cast<char *>(nullptr));
    ASSERT_EQ(array, const_cast<const char *>(result));
    ASSERT_STREQ(result, out_array);
}