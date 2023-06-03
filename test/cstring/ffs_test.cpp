#include <gtest/gtest.h>
#include "../../include/strings.h"

/* This part is ported from glibc fss test */

void do_try (const char *name, long long int param, int value, int expected)
{
    EXPECT_EQ(value, expected);
#if 0
  if (value != expected)
    {
      printf ("%s(%#llx) expected %d got %d\n",
          name, param, expected, value);
      support_record_failure ();
    }
  else
    printf ("%s(%#llx) as expected %d\n", name, param, value);
#endif
}


#define DO_TEST(fct, type) {\
  int i; \
  do_try (#fct, 0, fct ((type) 0), 0);					      \
  for (i=0 ; i < 8 * sizeof (type); i++)				      \
    do_try (#fct, 1ll << i, fct (((type) 1) << i), i + 1);			      \
  for (i=0 ; i < 8 * sizeof (type) ; i++)				      \
    do_try (#fct, (~((type) 0) >> i) << i, fct ((~((type) 0) >> i) << i), i + 1);\
  do_try (#fct, 0x80008000, fct ((type) 0x80008000), 16); } \


TEST(LibcFFsIntTest, Equal) {
    for (int i = 0; i < 1000; i++) {
        EXPECT_EQ(__MACONDO_TEST_NAMESPACE::ffs(i), __builtin_ffs(i));
    }

    DO_TEST (__MACONDO_TEST_NAMESPACE::ffs, int);
}

TEST(LibcFFsLongIntTest, Equal) {
    for (long int i = 0; i < 1000; i++) {
        EXPECT_EQ(__MACONDO_TEST_NAMESPACE::ffsl(i), __builtin_ffsl(i));
    }

    DO_TEST (__MACONDO_TEST_NAMESPACE::ffsl, long int);
}

TEST(LibcFFsLongLongIntTest, Equal) {
    for (long long int i = 0; i < 1000; i++) {
        EXPECT_EQ(__MACONDO_TEST_NAMESPACE::ffsll(i), __builtin_ffsll(i));
    }

    DO_TEST (__MACONDO_TEST_NAMESPACE::ffsll, long long int);
}
