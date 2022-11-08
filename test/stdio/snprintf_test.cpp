// This test ported from libslack
// https://github.com/ShivanKaul/libslack/blob/master/snprintf.c
// The idea is compare my implementation with version from standard library
#include <gtest/gtest.h>
#include "../../include/macondo/stdio.h"
#include <cstdio>

const char *int_fmt[] =
    {
        "%d", "%-d", "%+d", "% d", "%#d", "%0d", "%-+ #0d",
        "%9d", "%-9d", "%+9d", "% 9d", "%#9d", "%09d", "%-+ #09d",
        "%.9d", "%-.9d", "%+.9d", "% .9d", "%#.9d", "%0.9d", "%-+ #0.9d",
        "%9.d", "%-9.d", "%+9.d", "% 9.d", "%#9.d", "% 9.d", "%-+ #09.d",
        "%9.9d", "%-9.9d", "%+9.9d", "% 9.9d", "%#9.9d", "%09.9d", "%-+ #09.9d",
        "%.0d", "%-.0d", "%+.0d", "% .0d", "%#.0d", "%0.0d", "%-+ #0.0d",
        "%.1d", "%-.1d", "%+.1d", "% .1d", "%#.1d", "%0.1d", "%-+ #0.1d",
        "%.10000d", "%-.10000d", "%+.10000d", "% .10000d", "%#.10000d", "%0.10000d", "%-+ #0.10000d",
        "%10000d", "%-10000d", "%+10000d", "% 10000d", "%#10000d", "%010000d", "%-+ #010000d",
        "%10000.10000d", "%-10000.10000d", "%+10000.10000d", "% 10000.10000d", "%#10000.10000d", "%010000.10000d",
        "%-+ #010000.10000d",

        "%i", "%-i", "%+i", "% i", "%#i", "%0i", "%-+ #0i",
        "%9i", "%-9i", "%+9i", "% 9i", "%#9i", "%09i", "%-+ #09i",
        "%.9i", "%-.9i", "%+.9i", "% .9i", "%#.9i", "%0.9i", "%-+ #0.9i",
        "%9.i", "%-9.i", "%+9.i", "% 9.i", "%#9.i", "%09.i", "%-+ #09.i",
        "%9.9i", "%-9.9i", "%+9.9i", "% 9.9i", "%#9.9i", "%09.9i", "%-+ #09.9i",
        "%.0i", "%-.0i", "%+.0i", "% .0i", "%#.0i", "%0.0i", "%-+ #0.0i",
        "%.1i", "%-.1i", "%+.1i", "% .1i", "%#.1i", "%0.1i", "%-+ #0.1i",
        "%.10000i", "%-.10000i", "%+.10000i", "% .10000i", "%#.10000i", "%0.10000i", "%-+ #0.10000i",
        "%10000i", "%-10000i", "%+10000i", "% 10000i", "%#10000i", "%010000i", "%-+ #010000i",
        "%10000.10000i", "%-10000.10000i", "%+10000.10000i", "% 10000.10000i", "%#10000.10000i", "%010000.10000i",
        "%-+ #010000.10000i",

        "%-1.5d", "%1.5d", "%123.9d", "%5.5d", "%10.5d", "% 10.5d", "%+22.33d", "%01.3d", "%4d",
        "%-1.5i", "%1.5i", "%123.9i", "%5.5i", "%10.5i", "% 10.5i", "%+22.33i", "%01.3i", "%4i",
        NULL
    };

const char *int_fmt2[] =
    {
        "%*d", "%-*d", "%+*d", "% *d", "%#*d", "%0*d", "%-+ #0*d",
        "%*i", "%-*i", "%+*i", "% *i", "%#*i", "%0*i", "%-+ #0*i",
        NULL
    };

const char *int_fmt3[] =
    {
        "%.*d", "%-.*d", "%+.*d", "% .*d", "%#.*d", "%0.*d", "%-+ #0.*d",
        "%.*i", "%-.*i", "%+.*i", "% .*i", "%#.*i", "%0.*i", "%-+ #0.*i",
        NULL
    };

const char *int_fmt4[] =
    {
        "%*.*d", "%-*.*d", "%+*.*d", "% *.*d", "%#*.*d", "%0*.*d", "%-+ #0*.*d",
        "%*.*i", "%-*.*i", "%+*.*i", "% *.*i", "%#*.*i", "%0*.*i", "%-+ #0*.*i",
        NULL
    };

const char *hint_fmt[] =
    {
        "%hd", "%-hd", "%+hd", "% hd", "%#hd", "%0hd", "%-+ #0hd",
        "%9hd", "%-9hd", "%+9hd", "% 9hd", "%#9hd", "%09hd", "%-+ #09hd",
        "%.9hd", "%-.9hd", "%+.9hd", "% .9hd", "%#.9hd", "%0.9hd", "%-+ #0.9hd",
        "%9.hd", "%-9.hd", "%+9.hd", "% 9.hd", "%#9.hd", "%09.hd", "%-+ #09.hd",
        "%9.9hd", "%-9.9hd", "%+9.9hd", "% 9.9hd", "%#9.9hd", "%09.9hd", "%-+ #09.9hd",
        "%.0hd", "%-.0hd", "%+.0hd", "% .0hd", "%#.0hd", "%0.0hd", "%-+ #0.0hd",
        "%.1hd", "%-.1hd", "%+.1hd", "% .1hd", "%#.1hd", "%0.1hd", "%-+ #0.1hd",
        "%.10000hd", "%-.10000hd", "%+.10000hd", "% .10000hd", "%#.10000hd", "%0.10000hd", "%-+ #0.10000hd",
        "%10000hd", "%-10000hd", "%+10000hd", "% 10000hd", "%#10000hd", "%010000hd", "%-+ #010000hd",
        "%10000.10000hd", "%-10000.10000hd", "%+10000.10000hd", "% 10000.10000hd", "%#10000.10000hd", "%010000.10000hd",
        "%-+ #010000.10000hd",

        "%hi", "%-hi", "%+hi", "% hi", "%#hi", "%0hi", "%-+ #0hi",
        "%9hi", "%-9hi", "%+9hi", "% 9hi", "%#9hi", "%09hi", "%-+ #09hi",
        "%.9hi", "%-.9hi", "%+.9hi", "% .9hi", "%#.9hi", "%0.9hi", "%-+ #0.9hi",
        "%9.hi", "%-9.hi", "%+9.hi", "% 9.hi", "%#9.hi", "%09.hi", "%-+ #09.hi",
        "%9.9hi", "%-9.9hi", "%+9.9hi", "% 9.9hi", "%#9.9hi", "%09.9hi", "%-+ #09.9hi",
        "%.0hi", "%-.0hi", "%+.0hi", "% .0hi", "%#.0hi", "%0.0hi", "%-+ #0.0hi",
        "%.1hi", "%-.1hi", "%+.1hi", "% .1hi", "%#.1hi", "%0.1hi", "%-+ #0.1hi",
        "%.10000hi", "%-.10000hi", "%+.10000hi", "% .10000hi", "%#.10000hi", "%0.10000hi", "%-+ #0.10000hi",
        "%10000hi", "%-10000hi", "%+10000hi", "% 10000hi", "%#10000hi", "%010000hi", "%-+ #010000hi",
        "%10000.10000hi", "%-10000.10000hi", "%+10000.10000hi", "% 10000.10000hi", "%#10000.10000hi", "%010000.10000hi",
        "%-+ #010000.10000hi",

        "%-1.5hd", "%1.5hd", "%123.9hd", "%5.5hd", "%10.5hd", "% 10.5hd", "%+22.33hd", "%01.3hd", "%4hd",
        "%-1.5hi", "%1.5hi", "%123.9hi", "%5.5hi", "%10.5hi", "% 10.5hi", "%+22.33hi", "%01.3hi", "%4hi",
        NULL
    };

const char *hint_fmt2[] =
    {
        "%*hd", "%-*hd", "%+*hd", "% *hd", "%#*hd", "%0*hd", "%-+ #0*hd",
        "%*hi", "%-*hi", "%+*hi", "% *hi", "%#*hi", "%0*hi", "%-+ #0*hi",
        NULL
    };

const char *hint_fmt3[] =
    {
        "%.*hd", "%-.*hd", "%+.*hd", "% .*hd", "%#.*hd", "%0.*hd", "%-+ #0.*hd",
        "%.*hi", "%-.*hi", "%+.*hi", "% .*hi", "%#.*hi", "%0.*hi", "%-+ #0.*hi",
        NULL
    };

const char *hint_fmt4[] =
    {
        "%*.*hd", "%-*.*hd", "%+*.*hd", "% *.*hd", "%#*.*hd", "%0*.*hd", "%-+ #0*.*hd",
        "%*.*hi", "%-*.*hi", "%+*.*hi", "% *.*hi", "%#*.*hi", "%0*.*hi", "%-+ #0*.*hi",
        NULL
    };

const char *lint_fmt[] =
    {
        "%ld", "%-ld", "%+ld", "% ld", "%#ld", "%0ld", "%-+ #0ld",
        "%9ld", "%-9ld", "%+9ld", "% 9ld", "%#9ld", "%09ld", "%-+ #09ld",
        "%.9ld", "%-.9ld", "%+.9ld", "% .9ld", "%#.9ld", "%0.9ld", "%-+ #0.9ld",
        "%9.ld", "%-9.ld", "%+9.ld", "% 9.ld", "%#9.ld", "%09.ld", "%-+ #09.ld",
        "%9.9ld", "%-9.9ld", "%+9.9ld", "% 9.9ld", "%#9.9ld", "%09.9ld", "%-+ #09.9ld",
        "%.0ld", "%-.0ld", "%+.0ld", "% .0ld", "%#.0ld", "%0.0ld", "%-+ #0.0ld",
        "%.1ld", "%-.1ld", "%+.1ld", "% .1ld", "%#.1ld", "%0.1ld", "%-+ #0.1ld",
        "%.10000ld", "%-.10000ld", "%+.10000ld", "% .10000ld", "%#.10000ld", "%0.10000ld", "%-+ #0.10000ld",
        "%10000ld", "%-10000ld", "%+10000ld", "% 10000ld", "%#10000ld", "%010000ld", "%-+ #010000ld",
        "%10000.10000ld", "%-10000.10000ld", "%+10000.10000ld", "% 10000.10000ld", "%#10000.10000ld", "%010000.10000ld",
        "%-+ #010000.10000ld",

        "%li", "%-li", "%+li", "% li", "%#li", "%0li", "%-+ #0li",
        "%9li", "%-9li", "%+9li", "% 9li", "%#9li", "%09li", "%-+ #09li",
        "%.9li", "%-.9li", "%+.9li", "% .9li", "%#.9li", "%0.9li", "%-+ #0.9li",
        "%9.li", "%-9.li", "%+9.li", "% 9.li", "%#9.li", "%09.li", "%-+ #09.li",
        "%9.9li", "%-9.9li", "%+9.9li", "% 9.9li", "%#9.9li", "%09.9li", "%-+ #09.9li",
        "%.0li", "%-.0li", "%+.0li", "% .0li", "%#.0li", "%0.0li", "%-+ #0.0li",
        "%.1li", "%-.1li", "%+.1li", "% .1li", "%#.1li", "%0.1li", "%-+ #0.1li",
        "%.10000li", "%-.10000li", "%+.10000li", "% .10000li", "%#.10000li", "%0.10000li", "%-+ #0.10000li",
        "%10000li", "%-10000li", "%+10000li", "% 10000li", "%#10000li", "%010000li", "%-+ #010000li",
        "%10000.10000li", "%-10000.10000li", "%+10000.10000li", "% 10000.10000li", "%#10000.10000li", "%010000.10000li",
        "%-+ #010000.10000li",

        "%-1.5ld", "%1.5ld", "%123.9ld", "%5.5ld", "%10.5ld", "% 10.5ld", "%+22.33ld", "%01.3ld", "%4ld",
        "%-1.5li", "%1.5li", "%123.9li", "%5.5li", "%10.5li", "% 10.5li", "%+22.33li", "%01.3li", "%4li",
        NULL
    };

const char *lint_fmt2[] =
    {
        "%*ld", "%-*ld", "%+*ld", "% *ld", "%#*ld", "%0*ld", "%-+ #0*ld",
        "%*li", "%-*li", "%+*li", "% *li", "%#*li", "%0*li", "%-+ #0*li",
        NULL
    };

const char *lint_fmt3[] =
    {
        "%.*ld", "%-.*ld", "%+.*ld", "% .*ld", "%#.*ld", "%0.*ld", "%-+ #0.*ld",
        "%.*li", "%-.*li", "%+.*li", "% .*li", "%#.*li", "%0.*li", "%-+ #0.*li",
        NULL
    };

const char *lint_fmt4[] =
    {
        "%*.*ld", "%-*.*ld", "%+*.*ld", "% *.*ld", "%#*.*ld", "%0*.*ld", "%-+ #0*.*ld",
        "%*.*li", "%-*.*li", "%+*.*li", "% *.*li", "%#*.*li", "%0*.*li", "%-+ #0*.*li",
        NULL
    };

const char *uint_fmt[] =
    {
        "%o", "%-o", "%+o", "% o", "%#o", "%0o", "%-+ #0o",
        "%9o", "%-9o", "%+9o", "% 9o", "%#9o", "%09o", "%-+ #09o",
        "%.9o", "%-.9o", "%+.9o", "% .9o", "%#.9o", "%0.9o", "%-+ #0.9o",
        "%9.o", "%-9.o", "%+9.o", "% 9.o", "%#9.o", "%09.o", "%-+ #09.o",
        "%9.9o", "%-9.9o", "%+9.9o", "% 9.9o", "%#9.9o", "%09.9o", "%-+ #09.9o",
        "%.0o", "%-.0o", "%+.0o", "% .0o", "%#.0o", "%0.0o", "%-+ #0.0o",
        "%.1o", "%-.1o", "%+.1o", "% .1o", "%#.1o", "%0.1o", "%-+ #0.1o",
        "%.10000o", "%-.10000o", "%+.10000o", "% .10000o", "%#.10000o", "%0.10000o", "%-+ #0.10000o",
        "%10000o", "%-10000o", "%+10000o", "% 10000o", "%#10000o", "%010000o", "%-+ #010000o",
        "%10000.10000o", "%-10000.10000o", "%+10000.10000o", "% 10000.10000o", "%#10000.10000o", "%010000.10000o",
        "%-+ #010000.10000o",

        "%u", "%-u", "%+u", "% u", "%#u", "%0u", "%-+ #0u",
        "%9u", "%-9u", "%+9u", "% 9u", "%#9u", "%09u", "%-+ #09u",
        "%.9u", "%-.9u", "%+.9u", "% .9u", "%#.9u", "%0.9u", "%-+ #0.9u",
        "%9.u", "%-9.u", "%+9.u", "% 9.u", "%#9.u", "%09.u", "%-+ #09.u",
        "%9.9u", "%-9.9u", "%+9.9u", "% 9.9u", "%#9.9u", "%09.9u", "%-+ #09.9u",
        "%.0u", "%-.0u", "%+.0u", "% .0u", "%#.0u", "%0.0u", "%-+ #0.0u",
        "%.1u", "%-.1u", "%+.1u", "% .1u", "%#.1u", "%0.1u", "%-+ #0.1u",
        "%.10000u", "%-.10000u", "%+.10000u", "% .10000u", "%#.10000u", "%0.10000u", "%-+ #0.10000u",
        "%10000u", "%-10000u", "%+10000u", "% 10000u", "%#10000u", "%010000u", "%-+ #010000u",
        "%10000.10000u", "%-10000.10000u", "%+10000.10000u", "% 10000.10000u", "%#10000.10000u", "%010000.10000u",
        "%-+ #010000.10000u",

        "%x", "%-x", "%+x", "% x", "%#x", "%0x", "%-+ #0x",
        "%9x", "%-9x", "%+9x", "% 9x", "%#9x", "%09x", "%-+ #09x",
        "%.9x", "%-.9x", "%+.9x", "% .9x", "%#.9x", "%0.9x", "%-+ #0.9x",
        "%9.x", "%-9.x", "%+9.x", "% 9.x", "%#9.x", "%09.x", "%-+ #09.x",
        "%9.9x", "%-9.9x", "%+9.9x", "% 9.9x", "%#9.9x", "%09.9x", "%-+ #09.9x",
        "%.0x", "%-.0x", "%+.0x", "% .0x", "%#.0x", "%0.0x", "%-+ #0.0x",
        "%.1x", "%-.1x", "%+.1x", "% .1x", "%#.1x", "%0.1x", "%-+ #0.1x",
        "%.10000x", "%-.10000x", "%+.10000x", "% .10000x", "%#.10000x", "%0.10000x", "%-+ #0.10000x",
        "%10000x", "%-10000x", "%+10000x", "% 10000x", "%#10000x", "%010000x", "%-+ #010000x",
        "%10000.10000x", "%-10000.10000x", "%+10000.10000x", "% 10000.10000x", "%#10000.10000x", "%010000.10000x",
        "%-+ #010000.10000x",

        "%X", "%-X", "%+X", "% X", "%#X", "%0X", "%-+ #0X",
        "%9X", "%-9X", "%+9X", "% 9X", "%#9X", "%09X", "%-+ #09X",
        "%.9X", "%-.9X", "%+.9X", "% .9X", "%#.9X", "%0.9X", "%-+ #0.9X",
        "%9.X", "%-9.X", "%+9.X", "% 9.X", "%#9.X", "%09.X", "%-+ #09.X",
        "%9.9X", "%-9.9X", "%+9.9X", "% 9.9X", "%#9.9X", "%09.9X", "%-+ #09.9X",
        "%.0X", "%-.0X", "%+.0X", "% .0X", "%#.0X", "%0.0X", "%-+ #0.0X",
        "%.1X", "%-.1X", "%+.1X", "% .1X", "%#.1X", "%0.1X", "%-+ #0.1X",
        "%.10000X", "%-.10000X", "%+.10000X", "% .10000X", "%#.10000X", "%0.10000X", "%-+ #0.10000X",
        "%10000X", "%-10000X", "%+10000X", "% 10000X", "%#10000X", "%010000X", "%-+ #010000X",
        "%10000.10000X", "%-10000.10000X", "%+10000.10000X", "% 10000.10000X", "%#10000.10000X", "%010000.10000X",
        "%-+ #010000.10000X",

        "%p", "%-p", "%+p", "% p", "%#p", "%0p", "%-+ #0p",
        "%9p", "%-9p", "%+9p", "% 9p", "%#9p", "%09p", "%-+ #09p",
        "%.9p", "%-.9p", "%+.9p", "% .9p", "%#.9p", "%0.9p", "%-+ #0.9p",
        "%9.p", "%-9.p", "%+9.p", "% 9.p", "%#9.p", "%09.p", "%-+ #09.p",
        "%9.9p", "%-9.9p", "%+9.9p", "% 9.9p", "%#9.9p", "%09.9p", "%-+ #09.9p",
        "%.0p", "%-.0p", "%+.0p", "% .0p", "%#.0p", "%0.0p", "%-+ #0.0p",
        "%.1p", "%-.1p", "%+.1p", "% .1p", "%#.1p", "%0.1p", "%-+ #0.1p",
        "%.10000p", "%-.10000p", "%+.10000p", "% .10000p", "%#.10000p", "%0.10000p", "%-+ #0.10000p",
        "%10000p", "%-10000p", "%+10000p", "% 10000p", "%#10000p", "%010000p", "%-+ #010000p",
        "%10000.10000p", "%-10000.10000p", "%+10000.10000p", "% 10000.10000p", "%#10000.10000p", "%010000.10000p",
        "%-+ #010000.10000p",

        "%-1.5o", "%1.5o", "%123.9o", "%5.5o", "%10.5o", "% 10.5o", "%+22.33o", "%01.3o", "%4o",
        "%-1.5u", "%1.5u", "%123.9u", "%5.5u", "%10.5u", "% 10.5u", "%+22.33u", "%01.3u", "%4u",
        "%-1.5x", "%1.5x", "%123.9x", "%5.5x", "%10.5x", "% 10.5x", "%+22.33x", "%01.3x", "%4x",
        "%-1.5X", "%1.5X", "%123.9X", "%5.5X", "%10.5X", "% 10.5X", "%+22.33X", "%01.3X", "%4X",
        "%-1.5p", "%1.5p", "%123.9p", "%5.5p", "%10.5p", "% 10.5p", "%+22.33p", "%01.3p", "%4p",
        NULL
    };

const char *uint_fmt2[] =
    {
        "%*o", "%-*o", "%+*o", "% *o", "%#*o", "%0*o", "%-+ #0*o",
        "%*u", "%-*u", "%+*u", "% *u", "%#*u", "%0*u", "%-+ #0*u",
        "%*x", "%-*x", "%+*x", "% *x", "%#*x", "%0*x", "%-+ #0*x",
        "%*X", "%-*X", "%+*X", "% *X", "%#*X", "%0*X", "%-+ #0*X",
        "%*p", "%-*p", "%+*p", "% *p", "%#*p", "%0*p", "%-+ #0*p",
        NULL
    };

const char *uint_fmt3[] =
    {
        "%.*o", "%-.*o", "%+.*o", "% .*o", "%#.*o", "%0.*o", "%-+ #0.*o",
        "%.*u", "%-.*u", "%+.*u", "% .*u", "%#.*u", "%0.*u", "%-+ #0.*u",
        "%.*x", "%-.*x", "%+.*x", "% .*x", "%#.*x", "%0.*x", "%-+ #0.*x",
        "%.*X", "%-.*X", "%+.*X", "% .*X", "%#.*X", "%0.*X", "%-+ #0.*X",
        "%.*p", "%-.*p", "%+.*p", "% .*p", "%#.*p", "%0.*p", "%-+ #0.*p",
        NULL
    };

const char *uint_fmt4[] =
    {
        "%*.*o", "%-*.*o", "%+*.*o", "% *.*o", "%#*.*o", "%0*.*o", "%-+ #0*.*o",
        "%*.*u", "%-*.*u", "%+*.*u", "% *.*u", "%#*.*u", "%0*.*u", "%-+ #0*.*u",
        "%*.*x", "%-*.*x", "%+*.*x", "% *.*x", "%#*.*x", "%0*.*x", "%-+ #0*.*x",
        "%*.*X", "%-*.*X", "%+*.*X", "% *.*X", "%#*.*X", "%0*.*X", "%-+ #0*.*X",
        "%*.*p", "%-*.*p", "%+*.*p", "% *.*p", "%#*.*p", "%0*.*p", "%-+ #0*.*p",
        NULL
    };

const char *huint_fmt[] =
    {
        "%ho", "%-ho", "%+ho", "% ho", "%#ho", "%0ho", "%-+ #0ho",
        "%9ho", "%-9ho", "%+9ho", "% 9ho", "%#9ho", "%09ho", "%-+ #09ho",
        "%.9ho", "%-.9ho", "%+.9ho", "% .9ho", "%#.9ho", "%0.9ho", "%-+ #0.9ho",
        "%9.ho", "%-9.ho", "%+9.ho", "% 9.ho", "%#9.ho", "%09.ho", "%-+ #09.ho",
        "%9.9ho", "%-9.9ho", "%+9.9ho", "% 9.9ho", "%#9.9ho", "%09.9ho", "%-+ #09.9ho",
        "%.0ho", "%-.0ho", "%+.0ho", "% .0ho", "%#.0ho", "%0.0ho", "%-+ #0.0ho",
        "%.1ho", "%-.1ho", "%+.1ho", "% .1ho", "%#.1ho", "%0.1ho", "%-+ #0.1ho",
        "%.10000ho", "%-.10000ho", "%+.10000ho", "% .10000ho", "%#.10000ho", "%0.10000ho", "%-+ #0.10000ho",
        "%10000ho", "%-10000ho", "%+10000ho", "% 10000ho", "%#10000ho", "%010000ho", "%-+ #010000ho",
        "%10000.10000ho", "%-10000.10000ho", "%+10000.10000ho", "% 10000.10000ho", "%#10000.10000ho", "%010000.10000ho",
        "%-+ #010000.10000ho",

        "%hu", "%-hu", "%+hu", "% hu", "%#hu", "%0hu", "%-+ #0hu",
        "%9hu", "%-9hu", "%+9hu", "% 9hu", "%#9hu", "%09hu", "%-+ #09hu",
        "%.9hu", "%-.9hu", "%+.9hu", "% .9hu", "%#.9hu", "%0.9hu", "%-+ #0.9hu",
        "%9.hu", "%-9.hu", "%+9.hu", "% 9.hu", "%#9.hu", "%09.hu", "%-+ #09.hu",
        "%9.9hu", "%-9.9hu", "%+9.9hu", "% 9.9hu", "%#9.9hu", "%09.9hu", "%-+ #09.9hu",
        "%.0hu", "%-.0hu", "%+.0hu", "% .0hu", "%#.0hu", "%0.0hu", "%-+ #0.0hu",
        "%.1hu", "%-.1hu", "%+.1hu", "% .1hu", "%#.1hu", "%0.1hu", "%-+ #0.1hu",
        "%.10000hu", "%-.10000hu", "%+.10000hu", "% .10000hu", "%#.10000hu", "%0.10000hu", "%-+ #0.10000hu",
        "%10000hu", "%-10000hu", "%+10000hu", "% 10000hu", "%#10000hu", "%010000hu", "%-+ #010000hu",
        "%10000.10000hu", "%-10000.10000hu", "%+10000.10000hu", "% 10000.10000hu", "%#10000.10000hu", "%010000.10000hu",
        "%-+ #010000.10000hu",

        "%hx", "%-hx", "%+hx", "% hx", "%#hx", "%0hx", "%-+ #0hx",
        "%9hx", "%-9hx", "%+9hx", "% 9hx", "%#9hx", "%09hx", "%-+ #09hx",
        "%.9hx", "%-.9hx", "%+.9hx", "% .9hx", "%#.9hx", "%0.9hx", "%-+ #0.9hx",
        "%9.hx", "%-9.hx", "%+9.hx", "% 9.hx", "%#9.hx", "%09.hx", "%-+ #09.hx",
        "%9.9hx", "%-9.9hx", "%+9.9hx", "% 9.9hx", "%#9.9hx", "%09.9hx", "%-+ #09.9hx",
        "%.0hx", "%-.0hx", "%+.0hx", "% .0hx", "%#.0hx", "%0.0hx", "%-+ #0.0hx",
        "%.1hx", "%-.1hx", "%+.1hx", "% .1hx", "%#.1hx", "%0.1hx", "%-+ #0.1hx",
        "%.10000hx", "%-.10000hx", "%+.10000hx", "% .10000hx", "%#.10000hx", "%0.10000hx", "%-+ #0.10000hx",
        "%10000hx", "%-10000hx", "%+10000hx", "% 10000hx", "%#10000hx", "%010000hx", "%-+ #010000hx",
        "%10000.10000hx", "%-10000.10000hx", "%+10000.10000hx", "% 10000.10000hx", "%#10000.10000hx", "%010000.10000hx",
        "%-+ #010000.10000hx",

        "%hX", "%-hX", "%+hX", "% hX", "%#hX", "%0hX", "%-+ #0hX",
        "%9hX", "%-9hX", "%+9hX", "% 9hX", "%#9hX", "%09hX", "%-+ #09hX",
        "%.9hX", "%-.9hX", "%+.9hX", "% .9hX", "%#.9hX", "%0.9hX", "%-+ #0.9hX",
        "%9.hX", "%-9.hX", "%+9.hX", "% 9.hX", "%#9.hX", "%09.hX", "%-+ #09.hX",
        "%9.9hX", "%-9.9hX", "%+9.9hX", "% 9.9hX", "%#9.9hX", "%09.9hX", "%-+ #09.9hX",
        "%.0hX", "%-.0hX", "%+.0hX", "% .0hX", "%#.0hX", "%0.0hX", "%-+ #0.0hX",
        "%.1hX", "%-.1hX", "%+.1hX", "% .1hX", "%#.1hX", "%0.1hX", "%-+ #0.1hX",
        "%.10000hX", "%-.10000hX", "%+.10000hX", "% .10000hX", "%#.10000hX", "%0.10000hX", "%-+ #0.10000hX",
        "%10000hX", "%-10000hX", "%+10000hX", "% 10000hX", "%#10000hX", "%010000hX", "%-+ #010000hX",
        "%10000.10000hX", "%-10000.10000hX", "%+10000.10000hX", "% 10000.10000hX", "%#10000.10000hX", "%010000.10000hX",
        "%-+ #010000.10000hX",

        "%-1.5ho", "%1.5ho", "%123.9ho", "%5.5ho", "%10.5ho", "% 10.5ho", "%+22.33ho", "%01.3ho", "%4ho",
        "%-1.5hu", "%1.5hu", "%123.9hu", "%5.5hu", "%10.5hu", "% 10.5hu", "%+22.33hu", "%01.3hu", "%4hu",
        "%-1.5hx", "%1.5hx", "%123.9hx", "%5.5hx", "%10.5hx", "% 10.5hx", "%+22.33hx", "%01.3hx", "%4hx",
        "%-1.5hX", "%1.5hX", "%123.9hX", "%5.5hX", "%10.5hX", "% 10.5hX", "%+22.33hX", "%01.3hX", "%4hX",
        NULL
    };

const char *huint_fmt2[] =
    {
        "%*ho", "%-*ho", "%+*ho", "% *ho", "%#*ho", "%0*ho", "%-+ #0*ho",
        "%*hu", "%-*hu", "%+*hu", "% *hu", "%#*hu", "%0*hu", "%-+ #0*hu",
        "%*hx", "%-*hx", "%+*hx", "% *hx", "%#*hx", "%0*hx", "%-+ #0*hx",
        "%*hX", "%-*hX", "%+*hX", "% *hX", "%#*hX", "%0*hX", "%-+ #0*hX",
        NULL
    };

const char *huint_fmt3[] =
    {
        "%.*ho", "%-.*ho", "%+.*ho", "% .*ho", "%#.*ho", "%0.*ho", "%-+ #0.*ho",
        "%.*hu", "%-.*hu", "%+.*hu", "% .*hu", "%#.*hu", "%0.*hu", "%-+ #0.*hu",
        "%.*hx", "%-.*hx", "%+.*hx", "% .*hx", "%#.*hx", "%0.*hx", "%-+ #0.*hx",
        "%.*hX", "%-.*hX", "%+.*hX", "% .*hX", "%#.*hX", "%0.*hX", "%-+ #0.*hX",
        NULL
    };

const char *huint_fmt4[] =
    {
        "%*.*ho", "%-*.*ho", "%+*.*ho", "% *.*ho", "%#*.*ho", "%0*.*ho", "%-+ #0*.*ho",
        "%*.*hu", "%-*.*hu", "%+*.*hu", "% *.*hu", "%#*.*hu", "%0*.*hu", "%-+ #0*.*hu",
        "%*.*hx", "%-*.*hx", "%+*.*hx", "% *.*hx", "%#*.*hx", "%0*.*hx", "%-+ #0*.*hx",
        "%*.*hX", "%-*.*hX", "%+*.*hX", "% *.*hX", "%#*.*hX", "%0*.*hX", "%-+ #0*.*hX",
        NULL
    };

const char *luint_fmt[] =
    {
        "%lo", "%-lo", "%+lo", "% lo", "%#lo", "%0lo", "%-+ #0lo",
        "%9lo", "%-9lo", "%+9lo", "% 9lo", "%#9lo", "%09lo", "%-+ #09lo",
        "%.9lo", "%-.9lo", "%+.9lo", "% .9lo", "%#.9lo", "%0.9lo", "%-+ #0.9lo",
        "%9.lo", "%-9.lo", "%+9.lo", "% 9.lo", "%#9.lo", "%09.lo", "%-+ #09.lo",
        "%9.9lo", "%-9.9lo", "%+9.9lo", "% 9.9lo", "%#9.9lo", "%09.9lo", "%-+ #09.9lo",
        "%.0lo", "%-.0lo", "%+.0lo", "% .0lo", "%#.0lo", "%0.0lo", "%-+ #0.0lo",
        "%.1lo", "%-.1lo", "%+.1lo", "% .1lo", "%#.1lo", "%0.1lo", "%-+ #0.1lo",
        "%.10000lo", "%-.10000lo", "%+.10000lo", "% .10000lo", "%#.10000lo", "%0.10000lo", "%-+ #0.10000lo",
        "%10000lo", "%-10000lo", "%+10000lo", "% 10000lo", "%#10000lo", "%010000lo", "%-+ #010000lo",
        "%10000.10000lo", "%-10000.10000lo", "%+10000.10000lo", "% 10000.10000lo", "%#10000.10000lo", "%010000.10000lo",
        "%-+ #010000.10000lo",

        "%lu", "%-lu", "%+lu", "% lu", "%#lu", "%0lu", "%-+ #0lu",
        "%9lu", "%-9lu", "%+9lu", "% 9lu", "%#9lu", "%09lu", "%-+ #09lu",
        "%.9lu", "%-.9lu", "%+.9lu", "% .9lu", "%#.9lu", "%0.9lu", "%-+ #0.9lu",
        "%9.lu", "%-9.lu", "%+9.lu", "% 9.lu", "%#9.lu", "%09.lu", "%-+ #09.lu",
        "%9.9lu", "%-9.9lu", "%+9.9lu", "% 9.9lu", "%#9.9lu", "%09.9lu", "%-+ #09.9lu",
        "%.0lu", "%-.0lu", "%+.0lu", "% .0lu", "%#.0lu", "%0.0lu", "%-+ #0.0lu",
        "%.1lu", "%-.1lu", "%+.1lu", "% .1lu", "%#.1lu", "%0.1lu", "%-+ #0.1lu",
        "%.10000lu", "%-.10000lu", "%+.10000lu", "% .10000lu", "%#.10000lu", "%0.10000lu", "%-+ #0.10000lu",
        "%10000lu", "%-10000lu", "%+10000lu", "% 10000lu", "%#10000lu", "%010000lu", "%-+ #010000lu",
        "%10000.10000lu", "%-10000.10000lu", "%+10000.10000lu", "% 10000.10000lu", "%#10000.10000lu", "%010000.10000lu",
        "%-+ #010000.10000lu",

        "%lx", "%-lx", "%+lx", "% lx", "%#lx", "%0lx", "%-+ #0lx",
        "%9lx", "%-9lx", "%+9lx", "% 9lx", "%#9lx", "%09lx", "%-+ #09lx",
        "%.9lx", "%-.9lx", "%+.9lx", "% .9lx", "%#.9lx", "%0.9lx", "%-+ #0.9lx",
        "%9.lx", "%-9.lx", "%+9.lx", "% 9.lx", "%#9.lx", "%09.lx", "%-+ #09.lx",
        "%9.9lx", "%-9.9lx", "%+9.9lx", "% 9.9lx", "%#9.9lx", "%09.9lx", "%-+ #09.9lx",
        "%.0lx", "%-.0lx", "%+.0lx", "% .0lx", "%#.0lx", "%0.0lx", "%-+ #0.0lx",
        "%.1lx", "%-.1lx", "%+.1lx", "% .1lx", "%#.1lx", "%0.1lx", "%-+ #0.1lx",
        "%.10000lx", "%-.10000lx", "%+.10000lx", "% .10000lx", "%#.10000lx", "%0.10000lx", "%-+ #0.10000lx",
        "%10000lx", "%-10000lx", "%+10000lx", "% 10000lx", "%#10000lx", "%010000lx", "%-+ #010000lx",
        "%10000.10000lx", "%-10000.10000lx", "%+10000.10000lx", "% 10000.10000lx", "%#10000.10000lx", "%010000.10000lx",
        "%-+ #010000.10000lx",

        "%lX", "%-lX", "%+lX", "% lX", "%#lX", "%0lX", "%-+ #0lX",
        "%9lX", "%-9lX", "%+9lX", "% 9lX", "%#9lX", "%09lX", "%-+ #09lX",
        "%.9lX", "%-.9lX", "%+.9lX", "% .9lX", "%#.9lX", "%0.9lX", "%-+ #0.9lX",
        "%9.lX", "%-9.lX", "%+9.lX", "% 9.lX", "%#9.lX", "%09.lX", "%-+ #09.lX",
        "%9.9lX", "%-9.9lX", "%+9.9lX", "% 9.9lX", "%#9.9lX", "%09.9lX", "%-+ #09.9lX",
        "%.0lX", "%-.0lX", "%+.0lX", "% .0lX", "%#.0lX", "%0.0lX", "%-+ #0.0lX",
        "%.1lX", "%-.1lX", "%+.1lX", "% .1lX", "%#.1lX", "%0.1lX", "%-+ #0.1lX",
        "%.10000lX", "%-.10000lX", "%+.10000lX", "% .10000lX", "%#.10000lX", "%0.10000lX", "%-+ #0.10000lX",
        "%10000lX", "%-10000lX", "%+10000lX", "% 10000lX", "%#10000lX", "%010000lX", "%-+ #010000lX",
        "%10000.10000lX", "%-10000.10000lX", "%+10000.10000lX", "% 10000.10000lX", "%#10000.10000lX", "%010000.10000lX",
        "%-+ #010000.10000lX",

        "%-1.5lo", "%1.5lo", "%123.9lo", "%5.5lo", "%10.5lo", "% 10.5lo", "%+22.33lo", "%01.3lo", "%4lo",
        "%-1.5lu", "%1.5lu", "%123.9lu", "%5.5lu", "%10.5lu", "% 10.5lu", "%+22.33lu", "%01.3lu", "%4lu",
        "%-1.5lx", "%1.5lx", "%123.9lx", "%5.5lx", "%10.5lx", "% 10.5lx", "%+22.33lx", "%01.3lx", "%4lx",
        "%-1.5lX", "%1.5lX", "%123.9lX", "%5.5lX", "%10.5lX", "% 10.5lX", "%+22.33lX", "%01.3lX", "%4lX",
        NULL
    };

const char *luint_fmt2[] =
    {
        "%*lo", "%-*lo", "%+*lo", "% *lo", "%#*lo", "%0*lo", "%-+ #0*lo",
        "%*lu", "%-*lu", "%+*lu", "% *lu", "%#*lu", "%0*lu", "%-+ #0*lu",
        "%*lx", "%-*lx", "%+*lx", "% *lx", "%#*lx", "%0*lx", "%-+ #0*lx",
        "%*lX", "%-*lX", "%+*lX", "% *lX", "%#*lX", "%0*lX", "%-+ #0*lX",
        NULL
    };

const char *luint_fmt3[] =
    {
        "%.*lo", "%-.*lo", "%+.*lo", "% .*lo", "%#.*lo", "%0.*lo", "%-+ #0.*lo",
        "%.*lu", "%-.*lu", "%+.*lu", "% .*lu", "%#.*lu", "%0.*lu", "%-+ #0.*lu",
        "%.*lx", "%-.*lx", "%+.*lx", "% .*lx", "%#.*lx", "%0.*lx", "%-+ #0.*lx",
        "%.*lX", "%-.*lX", "%+.*lX", "% .*lX", "%#.*lX", "%0.*lX", "%-+ #0.*lX",
        NULL
    };

const char *luint_fmt4[] =
    {
        "%*.*lo", "%-*.*lo", "%+*.*lo", "% *.*lo", "%#*.*lo", "%0*.*lo", "%-+ #0*.*lo",
        "%*.*lu", "%-*.*lu", "%+*.*lu", "% *.*lu", "%#*.*lu", "%0*.*lu", "%-+ #0*.*lu",
        "%*.*lx", "%-*.*lx", "%+*.*lx", "% *.*lx", "%#*.*lx", "%0*.*lx", "%-+ #0*.*lx",
        "%*.*lX", "%-*.*lX", "%+*.*lX", "% *.*lX", "%#*.*lX", "%0*.*lX", "%-+ #0*.*lX",
        NULL
    };

unsigned long uint_nums[] =
    {
        ULONG_MAX, 0xffffffff, 134, 91340, 341, 0203, 0, 0xffff3333
    };

const char *str_fmt[] =
    {
        "%s", "%-s",
        "%9s", "%-9s",
        "%.9s", "%-.9s",
        "%9.s", "%-9.s",
        "%9.9s", "%-9.9s",
        "%.0s", "%-.0s",
        "%.1s", "%-.1s",
        "%.10000s", "%-.10000s",
        "%10000s", "%-10000s",
        "%10000.10000s", "%-10000.10000s",
        NULL
    };

const char *str_fmt2[] =
    {
        "%*s", "%-*s",
        NULL
    };

const char *str_fmt3[] =
    {
        "%.*s", "%-.*s",
        NULL
    };

const char *str_fmt4[] =
    {
        "%*.*s", "%-*.*s",
        NULL
    };

const char *str_vals[] =
    {
#ifdef HAVE_PRINTF_STR_FMT_NULL
        NULL,
#endif
        "", "a", "ab", "abc", "abcdefgh", "abcdefghi",
        "abcdefghij", "abcdefghijk", "abcdef\000ghijk"
    };

const char *char_fmt[] =
    {
        "%c", "%-c",
        "%1c", "%-1c",
        "%2c", "%-2c",
        "%3c", "%-3c",
        "%4c", "%-4c",
        NULL
    };

const char *char_fmt2[] =
    {
        "%*c", "%-*c",
        NULL
    };

const char *char_fmt3[] =
    {
        "%.*c", "%-.*c",
        NULL
    };

const char *char_fmt4[] =
    {
        "%*.*c", "%-*.*c",
        NULL
    };

char char_vals[] =
    {
        'a', '\0', '\377'
    };

int widths[] = {0, 0, 15, 15, 1, 0, 80, 80, 0, -15, -15, -80};
int precisions[] = {0, 15, 0, 15, 1, 80, 0, 80, -15, 0, -15, -80};
long int_nums[] = {LONG_LONG_MIN, -1, 134, 91340, 341, 0203, 0, -12345, LONG_LONG_MAX};

#define BUFFER_SIZE 10000 * 2

TEST(MacondoLibcSnprintfTest, ShortNumbers) {
    char buffer[BUFFER_SIZE];
    char std_buffer[BUFFER_SIZE];
    int std_res = 0;
    int res = 0;

    for (int x = 0; hint_fmt[x]; ++x) {
        for (int y = 0; y < sizeof(int_nums) / sizeof(*int_nums); ++y) {
            std_res = ::snprintf(std_buffer, BUFFER_SIZE, hint_fmt[x], (int) int_nums[y]);
            res = __MACONDO_TEST_NAMESPACE::snprintf(buffer, BUFFER_SIZE, hint_fmt[x], (short) int_nums[y]);
            ASSERT_EQ(std_res, res);
            ASSERT_STREQ(std_buffer, buffer);
        }
    }

    for (int x = 0; hint_fmt2[x]; ++x) {
        for (int y = 0; y < sizeof(int_nums) / sizeof(*int_nums); ++y) {
            for (int z = 0; z < sizeof(widths) / sizeof(*widths); ++z) {
                std_res = ::snprintf(std_buffer, BUFFER_SIZE, hint_fmt2[x], widths[z], (short) int_nums[y]);
                res =
                    __MACONDO_TEST_NAMESPACE::snprintf(buffer,
                                                       BUFFER_SIZE,
                                                       hint_fmt2[x],
                                                       widths[z],
                                                       (short) int_nums[y]);
                ASSERT_EQ(std_res, res);
                ASSERT_STREQ(std_buffer, buffer);
            }
        }
    }

    for (int x = 0; hint_fmt3[x]; ++x) {
        for (int y = 0; y < sizeof(int_nums) / sizeof(*int_nums); ++y) {
            for (int z = 0; z < sizeof(widths) / sizeof(*widths); ++z) {
                std_res = ::snprintf(std_buffer, BUFFER_SIZE, hint_fmt3[x], precisions[z], (short) int_nums[y]);
                res =
                    __MACONDO_TEST_NAMESPACE::snprintf(buffer,
                                                       BUFFER_SIZE,
                                                       hint_fmt3[x],
                                                       precisions[z],
                                                       (short) int_nums[y]);
                ASSERT_EQ(std_res, res);
                ASSERT_STREQ(std_buffer, buffer);
            }
        }
    }

    for (int x = 0; hint_fmt4[x]; ++x) {
        for (int y = 0; y < sizeof(int_nums) / sizeof(*int_nums); ++y) {
            for (int z = 0; z < sizeof(widths) / sizeof(*widths); ++z) {
                std_res =
                    ::snprintf(std_buffer, BUFFER_SIZE, hint_fmt4[x], widths[z], precisions[z], (short) int_nums[y]);
                res =
                    __MACONDO_TEST_NAMESPACE::snprintf(buffer,
                                                       BUFFER_SIZE,
                                                       hint_fmt4[x],
                                                       widths[z],
                                                       precisions[z],
                                                       (short) int_nums[y]);
                ASSERT_EQ(std_res, res);
                ASSERT_STREQ(std_buffer, buffer);
            }
        }
    }
}

TEST(MacondoLibcSnprintfTest, IntNumbers) {
    char buffer[BUFFER_SIZE];
    char std_buffer[BUFFER_SIZE];
    int std_res = 0;
    int res = 0;

    for (int x = 0; int_fmt[x]; ++x) {
        for (int y = 0; y < sizeof(int_nums) / sizeof(*int_nums); ++y) {
            std_res = ::snprintf(std_buffer, BUFFER_SIZE, int_fmt[x], (int) int_nums[y]);
            res = __MACONDO_TEST_NAMESPACE::snprintf(buffer, BUFFER_SIZE, int_fmt[x], (int) int_nums[y]);
            ASSERT_EQ(std_res, res);
            ASSERT_STREQ(std_buffer, buffer);
        }
    }

    for (int x = 0; int_fmt2[x]; ++x) {
        for (int y = 0; y < sizeof(int_nums) / sizeof(*int_nums); ++y) {
            for (int z = 0; z < sizeof(widths) / sizeof(*widths); ++z) {
                std_res = ::snprintf(std_buffer, BUFFER_SIZE, int_fmt2[x], widths[z], (int) int_nums[y]);
                res =
                    __MACONDO_TEST_NAMESPACE::snprintf(buffer, BUFFER_SIZE, int_fmt2[x], widths[z], (int) int_nums[y]);
                ASSERT_EQ(std_res, res);
                ASSERT_STREQ(std_buffer, buffer);
            }
        }
    }

    for (int x = 0; int_fmt3[x]; ++x) {
        for (int y = 0; y < sizeof(int_nums) / sizeof(*int_nums); ++y) {
            for (int z = 0; z < sizeof(widths) / sizeof(*widths); ++z) {
                std_res = ::snprintf(std_buffer, BUFFER_SIZE, int_fmt3[x], precisions[z], (int) int_nums[y]);
                res =
                    __MACONDO_TEST_NAMESPACE::snprintf(buffer,
                                                       BUFFER_SIZE,
                                                       int_fmt3[x],
                                                       precisions[z],
                                                       (int) int_nums[y]);
                ASSERT_EQ(std_res, res);
                ASSERT_STREQ(std_buffer, buffer);
            }
        }
    }

    for (int x = 0; int_fmt4[x]; ++x) {
        for (int y = 0; y < sizeof(int_nums) / sizeof(*int_nums); ++y) {
            for (int z = 0; z < sizeof(widths) / sizeof(*widths); ++z) {
                std_res = ::snprintf(std_buffer, BUFFER_SIZE, int_fmt4[x], widths[z], precisions[z], (int) int_nums[y]);
                res =
                    __MACONDO_TEST_NAMESPACE::snprintf(buffer,
                                                       BUFFER_SIZE,
                                                       int_fmt4[x],
                                                       widths[z],
                                                       precisions[z],
                                                       (int) int_nums[y]);
                ASSERT_EQ(std_res, res);
                ASSERT_STREQ(std_buffer, buffer);
            }
        }
    }
}

TEST(MacondoLibcSnprintfTest, LongNumbers) {
    char buffer[BUFFER_SIZE];
    char std_buffer[BUFFER_SIZE];
    int std_res = 0;
    int res = 0;

    for (int x = 0; lint_fmt[x]; ++x) {
        for (int y = 0; y < sizeof(int_nums) / sizeof(*int_nums); ++y) {
            std_res = ::snprintf(std_buffer, BUFFER_SIZE, lint_fmt[x], (int) int_nums[y]);
            res = __MACONDO_TEST_NAMESPACE::snprintf(buffer, BUFFER_SIZE, lint_fmt[x], int_nums[y]);
            ASSERT_EQ(std_res, res);
            ASSERT_STREQ(std_buffer, buffer);
        }
    }

    for (int x = 0; lint_fmt2[x]; ++x) {
        for (int y = 0; y < sizeof(int_nums) / sizeof(*int_nums); ++y) {
            for (int z = 0; z < sizeof(widths) / sizeof(*widths); ++z) {
                std_res = ::snprintf(std_buffer, BUFFER_SIZE, lint_fmt2[x], widths[z], int_nums[y]);
                res =
                    __MACONDO_TEST_NAMESPACE::snprintf(buffer,
                                                       BUFFER_SIZE,
                                                       lint_fmt2[x],
                                                       widths[z],
                                                       int_nums[y]);
                ASSERT_EQ(std_res, res);
                ASSERT_STREQ(std_buffer, buffer);
            }
        }
    }

    for (int x = 0; lint_fmt3[x]; ++x) {
        for (int y = 0; y < sizeof(int_nums) / sizeof(*int_nums); ++y) {
            for (int z = 0; z < sizeof(widths) / sizeof(*widths); ++z) {
                std_res = ::snprintf(std_buffer, BUFFER_SIZE, lint_fmt3[x], precisions[z], int_nums[y]);
                res =
                    __MACONDO_TEST_NAMESPACE::snprintf(buffer,
                                                       BUFFER_SIZE,
                                                       lint_fmt3[x],
                                                       precisions[z],
                                                       int_nums[y]);
                ASSERT_EQ(std_res, res);
                ASSERT_STREQ(std_buffer, buffer);
            }
        }
    }

    for (int x = 0; lint_fmt4[x]; ++x) {
        for (int y = 0; y < sizeof(int_nums) / sizeof(*int_nums); ++y) {
            for (int z = 0; z < sizeof(widths) / sizeof(*widths); ++z) {
                std_res =
                    ::snprintf(std_buffer, BUFFER_SIZE, lint_fmt4[x], widths[z], precisions[z], (int) int_nums[y]);
                res =
                    __MACONDO_TEST_NAMESPACE::snprintf(buffer,
                                                       BUFFER_SIZE,
                                                       lint_fmt4[x],
                                                       widths[z],
                                                       precisions[z],
                                                       int_nums[y]);
                ASSERT_EQ(std_res, res);
                ASSERT_STREQ(std_buffer, buffer);
            }
        }
    }
}

TEST(MacondoLibcSnprintfTest, UnsignedShortNumbers) {
    char buffer[BUFFER_SIZE];
    char std_buffer[BUFFER_SIZE];
    int std_res = 0;
    int res = 0;

    for (int x = 0; hint_fmt[x]; ++x) {
        for (int y = 0; y < sizeof(uint_nums) / sizeof(*uint_nums); ++y) {
            std_res = ::snprintf(std_buffer, BUFFER_SIZE, huint_fmt[x], (unsigned short) uint_nums[y]);
            res = __MACONDO_TEST_NAMESPACE::snprintf(buffer, BUFFER_SIZE, huint_fmt[x], (unsigned short) uint_nums[y]);
            ASSERT_EQ(std_res, res);
            ASSERT_STREQ(std_buffer, buffer);
        }
    }

    for (int x = 0; hint_fmt2[x]; ++x) {
        for (int y = 0; y < sizeof(uint_nums) / sizeof(*uint_nums); ++y) {
            for (int z = 0; z < sizeof(widths) / sizeof(*widths); ++z) {
                std_res = ::snprintf(std_buffer, BUFFER_SIZE, huint_fmt2[x], widths[z], (unsigned short) uint_nums[y]);
                res =
                    __MACONDO_TEST_NAMESPACE::snprintf(buffer,
                                                       BUFFER_SIZE,
                                                       huint_fmt2[x],
                                                       widths[z],
                                                       (unsigned short) uint_nums[y]);
                ASSERT_EQ(std_res, res);
                ASSERT_STREQ(std_buffer, buffer);
            }
        }
    }

    for (int x = 0; hint_fmt3[x]; ++x) {
        for (int y = 0; y < sizeof(uint_nums) / sizeof(*uint_nums); ++y) {
            for (int z = 0; z < sizeof(widths) / sizeof(*widths); ++z) {
                std_res =
                    ::snprintf(std_buffer, BUFFER_SIZE, huint_fmt3[x], precisions[z], (unsigned short) uint_nums[y]);
                res =
                    __MACONDO_TEST_NAMESPACE::snprintf(buffer,
                                                       BUFFER_SIZE,
                                                       huint_fmt3[x],
                                                       precisions[z],
                                                       (unsigned short) uint_nums[y]);
                ASSERT_EQ(std_res, res);
                ASSERT_STREQ(std_buffer, buffer);
            }
        }
    }

    for (int x = 0; hint_fmt4[x]; ++x) {
        for (int y = 0; y < sizeof(uint_nums) / sizeof(*uint_nums); ++y) {
            for (int z = 0; z < sizeof(widths) / sizeof(*widths); ++z) {
                std_res =
                    ::snprintf(std_buffer,
                               BUFFER_SIZE,
                               huint_fmt4[x],
                               widths[z],
                               precisions[z],
                               (unsigned short) uint_nums[y]);
                res =
                    __MACONDO_TEST_NAMESPACE::snprintf(buffer,
                                                       BUFFER_SIZE,
                                                       huint_fmt4[x],
                                                       widths[z],
                                                       precisions[z],
                                                       (unsigned short) uint_nums[y]);
                ASSERT_EQ(std_res, res);
                ASSERT_STREQ(std_buffer, buffer);
            }
        }
    }
}

TEST(MacondoLibcSnprintfTest, UnsignedIntNumbers) {
    char buffer[BUFFER_SIZE];
    char std_buffer[BUFFER_SIZE];
    int std_res = 0;
    int res = 0;

    for (int x = 0; int_fmt[x]; ++x) {
        for (int y = 0; y < sizeof(uint_nums) / sizeof(*uint_nums); ++y) {
            std_res = ::snprintf(std_buffer, BUFFER_SIZE, uint_fmt[x], (unsigned int) uint_nums[y]);
            res = __MACONDO_TEST_NAMESPACE::snprintf(buffer, BUFFER_SIZE, uint_fmt[x], (unsigned int) uint_nums[y]);
            ASSERT_EQ(std_res, res);
            ASSERT_STREQ(std_buffer, buffer);
        }
    }

    for (int x = 0; int_fmt2[x]; ++x) {
        for (int y = 0; y < sizeof(uint_nums) / sizeof(*uint_nums); ++y) {
            for (int z = 0; z < sizeof(widths) / sizeof(*widths); ++z) {
                std_res = ::snprintf(std_buffer, BUFFER_SIZE, uint_fmt2[x], widths[z], (unsigned int) uint_nums[y]);
                res =
                    __MACONDO_TEST_NAMESPACE::snprintf(buffer,
                                                       BUFFER_SIZE,
                                                       uint_fmt2[x],
                                                       widths[z],
                                                       (unsigned int) uint_nums[y]);
                ASSERT_EQ(std_res, res);
                ASSERT_STREQ(std_buffer, buffer);
            }
        }
    }

    for (int x = 0; int_fmt3[x]; ++x) {
        for (int y = 0; y < sizeof(uint_nums) / sizeof(*uint_nums); ++y) {
            for (int z = 0; z < sizeof(widths) / sizeof(*widths); ++z) {
                std_res = ::snprintf(std_buffer, BUFFER_SIZE, uint_fmt3[x], precisions[z], (unsigned int) uint_nums[y]);
                res =
                    __MACONDO_TEST_NAMESPACE::snprintf(buffer,
                                                       BUFFER_SIZE,
                                                       uint_fmt3[x],
                                                       precisions[z],
                                                       (unsigned int) uint_nums[y]);
                ASSERT_EQ(std_res, res);
                ASSERT_STREQ(std_buffer, buffer);
            }
        }
    }

    for (int x = 0; int_fmt4[x]; ++x) {
        for (int y = 0; y < sizeof(uint_nums) / sizeof(*uint_nums); ++y) {
            for (int z = 0; z < sizeof(widths) / sizeof(*widths); ++z) {
                std_res = ::snprintf(std_buffer,
                                     BUFFER_SIZE,
                                     uint_fmt4[x],
                                     widths[z],
                                     precisions[z],
                                     (unsigned int) uint_nums[y]);
                res =
                    __MACONDO_TEST_NAMESPACE::snprintf(buffer,
                                                       BUFFER_SIZE,
                                                       uint_fmt4[x],
                                                       widths[z],
                                                       precisions[z],
                                                       (unsigned int) uint_nums[y]);
                ASSERT_EQ(std_res, res);
                ASSERT_STREQ(std_buffer, buffer);
            }
        }
    }
}

TEST(MacondoLibcSnprintfTest, UnsignedLongNumbers) {
    char buffer[BUFFER_SIZE];
    char std_buffer[BUFFER_SIZE];
    int std_res = 0;
    int res = 0;

    for (int x = 0; int_fmt[x]; ++x) {
        for (int y = 0; y < sizeof(uint_nums) / sizeof(*uint_nums); ++y) {
            std_res = ::snprintf(std_buffer, BUFFER_SIZE, luint_fmt[x], (unsigned long) uint_nums[y]);
            res = __MACONDO_TEST_NAMESPACE::snprintf(buffer, BUFFER_SIZE, luint_fmt[x], (unsigned long) uint_nums[y]);
            ASSERT_EQ(std_res, res);
            ASSERT_STREQ(std_buffer, buffer);
        }
    }

    for (int x = 0; int_fmt2[x]; ++x) {
        for (int y = 0; y < sizeof(uint_nums) / sizeof(*uint_nums); ++y) {
            for (int z = 0; z < sizeof(widths) / sizeof(*widths); ++z) {
                std_res = ::snprintf(std_buffer, BUFFER_SIZE, luint_fmt2[x], widths[z], (unsigned long) uint_nums[y]);
                res =
                    __MACONDO_TEST_NAMESPACE::snprintf(buffer,
                                                       BUFFER_SIZE,
                                                       luint_fmt2[x],
                                                       widths[z],
                                                       (unsigned long) uint_nums[y]);
                ASSERT_EQ(std_res, res);
                ASSERT_STREQ(std_buffer, buffer);
            }
        }
    }

    for (int x = 0; int_fmt3[x]; ++x) {
        for (int y = 0; y < sizeof(uint_nums) / sizeof(*uint_nums); ++y) {
            for (int z = 0; z < sizeof(widths) / sizeof(*widths); ++z) {
                std_res =
                    ::snprintf(std_buffer, BUFFER_SIZE, luint_fmt3[x], precisions[z], (unsigned long) uint_nums[y]);
                res =
                    __MACONDO_TEST_NAMESPACE::snprintf(buffer,
                                                       BUFFER_SIZE,
                                                       luint_fmt3[x],
                                                       precisions[z],
                                                       (unsigned long) uint_nums[y]);
                ASSERT_EQ(std_res, res);
                ASSERT_STREQ(std_buffer, buffer);
            }
        }
    }

    for (int x = 0; int_fmt4[x]; ++x) {
        for (int y = 0; y < sizeof(uint_nums) / sizeof(*uint_nums); ++y) {
            for (int z = 0; z < sizeof(widths) / sizeof(*widths); ++z) {
                std_res = ::snprintf(std_buffer,
                                     BUFFER_SIZE,
                                     luint_fmt4[x],
                                     widths[z],
                                     precisions[z],
                                     (unsigned int) uint_nums[y]);
                res =
                    __MACONDO_TEST_NAMESPACE::snprintf(buffer,
                                                       BUFFER_SIZE,
                                                       luint_fmt4[x],
                                                       widths[z],
                                                       precisions[z],
                                                       (unsigned int) uint_nums[y]);
                ASSERT_EQ(std_res, res);
                ASSERT_STREQ(std_buffer, buffer);
            }
        }
    }
}

TEST(MacondoLibcSnprintfTest, Strings) {
    char buffer[BUFFER_SIZE];
    char std_buffer[BUFFER_SIZE];
    int std_res = 0;
    int res = 0;

    for (int x = 0; str_fmt[x]; ++x) {
        for (int y = 0; y < sizeof(str_vals) / sizeof(*str_vals); ++y) {
            std_res = ::snprintf(std_buffer, BUFFER_SIZE, str_fmt[x], str_vals[y]);
            res = __MACONDO_TEST_NAMESPACE::snprintf(buffer, BUFFER_SIZE, str_fmt[x], str_vals[y]);
            ASSERT_EQ(std_res, res);
            ASSERT_STREQ(std_buffer, buffer);
        }
    }

    for (int x = 0; str_fmt2[x]; ++x) {
        for (int y = 0; y < sizeof(str_vals) / sizeof(*str_vals); ++y) {
            for (int z = 0; z < sizeof(widths) / sizeof(*widths); ++z) {
                std_res = ::snprintf(std_buffer, BUFFER_SIZE, str_fmt2[x], widths[z], str_vals[y]);
                res =
                    __MACONDO_TEST_NAMESPACE::snprintf(buffer,
                                                       BUFFER_SIZE,
                                                       str_fmt2[x],
                                                       widths[z],
                                                       str_vals[y]);
                ASSERT_EQ(std_res, res);
                ASSERT_STREQ(std_buffer, buffer);
            }
        }
    }

    for (int x = 0; str_fmt3[x]; ++x) {
        for (int y = 0; y < sizeof(str_vals) / sizeof(*str_vals); ++y) {
            for (int z = 0; z < sizeof(widths) / sizeof(*widths); ++z) {
                std_res =
                    ::snprintf(std_buffer, BUFFER_SIZE, str_fmt3[x], precisions[z], str_vals[y]);
                res =
                    __MACONDO_TEST_NAMESPACE::snprintf(buffer,
                                                       BUFFER_SIZE,
                                                       str_fmt3[x],
                                                       precisions[z],
                                                       str_vals[y]);
                ASSERT_EQ(std_res, res);
                ASSERT_STREQ(std_buffer, buffer);
            }
        }
    }

    for (int x = 0; str_fmt4[x]; ++x) {
        for (int y = 0; y < sizeof(str_vals) / sizeof(*str_vals); ++y) {
            for (int z = 0; z < sizeof(widths) / sizeof(*widths); ++z) {
                std_res = ::snprintf(std_buffer,
                                     BUFFER_SIZE,
                                     str_fmt4[x],
                                     widths[z],
                                     precisions[z],
                                     str_vals[y]);
                res =
                    __MACONDO_TEST_NAMESPACE::snprintf(buffer,
                                                       BUFFER_SIZE,
                                                       str_fmt4[x],
                                                       widths[z],
                                                       precisions[z],
                                                       str_vals[y]);
                ASSERT_EQ(std_res, res);
                ASSERT_STREQ(std_buffer, buffer);
            }
        }
    }
}

TEST(MacondoLibcSnprintfTest, Characters) {
    char buffer[BUFFER_SIZE];
    char std_buffer[BUFFER_SIZE];
    int std_res = 0;
    int res = 0;

    for (int x = 0; char_fmt[x]; ++x) {
        for (int y = 0; y < sizeof(char_vals) / sizeof(*char_vals); ++y) {
            std_res = ::snprintf(std_buffer, BUFFER_SIZE, char_fmt[x], char_vals[y]);
            res = __MACONDO_TEST_NAMESPACE::snprintf(buffer, BUFFER_SIZE, char_fmt[x], char_vals[y]);
            ASSERT_EQ(std_res, res);
            ASSERT_STREQ(std_buffer, buffer);
        }
    }

    for (int x = 0; char_fmt2[x]; ++x) {
        for (int y = 0; y < sizeof(char_vals) / sizeof(*char_vals); ++y) {
            for (int z = 0; z < sizeof(widths) / sizeof(*widths); ++z) {
                std_res = ::snprintf(std_buffer, BUFFER_SIZE, char_fmt2[x], widths[z], char_vals[y]);
                res =
                    __MACONDO_TEST_NAMESPACE::snprintf(buffer,
                                                       BUFFER_SIZE,
                                                       char_fmt2[x],
                                                       widths[z],
                                                       char_vals[y]);
                ASSERT_EQ(std_res, res);
                ASSERT_STREQ(std_buffer, buffer);
            }
        }
    }

    for (int x = 0; char_fmt3[x]; ++x) {
        for (int y = 0; y < sizeof(char_vals) / sizeof(*char_vals); ++y) {
            for (int z = 0; z < sizeof(widths) / sizeof(*widths); ++z) {
                std_res =
                    ::snprintf(std_buffer, BUFFER_SIZE, char_fmt3[x], precisions[z], char_vals[y]);
                res =
                    __MACONDO_TEST_NAMESPACE::snprintf(buffer,
                                                       BUFFER_SIZE,
                                                       char_fmt3[x],
                                                       precisions[z],
                                                       char_vals[y]);
                ASSERT_EQ(std_res, res);
                ASSERT_STREQ(std_buffer, buffer);
            }
        }
    }

    for (int x = 0; char_fmt4[x]; ++x) {
        for (int y = 0; y < sizeof(char_vals) / sizeof(*char_vals); ++y) {
            for (int z = 0; z < sizeof(widths) / sizeof(*widths); ++z) {
                std_res = ::snprintf(std_buffer,
                                     BUFFER_SIZE,
                                     char_fmt4[x],
                                     widths[z],
                                     precisions[z],
                                     char_vals[y]);
                res =
                    __MACONDO_TEST_NAMESPACE::snprintf(buffer,
                                                       BUFFER_SIZE,
                                                       char_fmt4[x],
                                                       widths[z],
                                                       precisions[z],
                                                       char_vals[y]);
                ASSERT_EQ(std_res, res);
                ASSERT_STREQ(std_buffer, buffer);
            }
        }
    }
}