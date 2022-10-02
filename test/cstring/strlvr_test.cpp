#include <gtest/gtest.h>
#include "../../include/string.h"

TEST(LibcStrLvrTest, EmptyString) {
    char empty[] = {""};

    char *result = __STD_NAMESPACE::strupr(empty);
    ASSERT_NE(result, static_cast<char *>(nullptr));
    ASSERT_EQ(empty, const_cast<const char *>(result));
    ASSERT_STREQ(empty, result);
}

TEST(LibcStrLvrTest, TextString) {
    char array[] = {"Hello World!"};
    char out_array[] = {"HELLO WORLD!"};

    char *result = __STD_NAMESPACE::strupr(array);
    ASSERT_NE(result, static_cast<char *>(nullptr));
    ASSERT_EQ(array, const_cast<const char *>(result));
    ASSERT_STREQ(result, out_array);
}