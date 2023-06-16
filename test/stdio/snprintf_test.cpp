/*
 * Copyright (c) 2011 The tyndur Project. All rights reserved.
 *
 * This code is derived from software contributed to the tyndur Project
 * by Kevin Wolf.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <gtest/gtest.h>
#include "../../include/macondo/stdio.h"
#include <cstdio>

static constexpr const char *kNull = "(null)";
static constexpr const char *kNil = "(nil)";
#define BUFFER_SIZE 10000 * 2

#define DO_TEST(buf, ret, fmt, ...) do { \
        char lbuf[64] = { 0 }; \
        int lret = __MACONDO_TEST_NAMESPACE::sprintf(lbuf, fmt, ## __VA_ARGS__); \
        ASSERT_EQ(ret, lret);                                     \
        ASSERT_STREQ(lbuf, buf);          \
    } while(0);

TEST(MacondoGenericVsnprintfTest, GenericTest) {
    int failed = 0;

    /* Ein String ohne alles */
    DO_TEST("Hallo heimur", 12, "Hallo heimur")

    /* Einfache Konvertierungen */
    DO_TEST("Hallo heimur",   12, "%s",       "Hallo heimur")
    DO_TEST("1024",            4, "%d",       1024)
    DO_TEST("-1024",           5, "%d",       -1024)
    DO_TEST("1024",            4, "%i",       1024)
    DO_TEST("-1024",           5, "%i",       -1024)
    DO_TEST("1024",            4, "%u",       1024u)
    DO_TEST("4294966272",     10, "%u",       -1024u)
    DO_TEST("777",             3, "%o",       0777u)
    DO_TEST("37777777001",    11, "%o",       -0777u)
    DO_TEST("1234abcd",        8, "%x",       0x1234abcdu)
    DO_TEST("edcb5433",        8, "%x",       -0x1234abcdu)
    DO_TEST("1234ABCD",        8, "%X",       0x1234abcdu)
    DO_TEST("EDCB5433",        8, "%X",       -0x1234abcdu)
    DO_TEST("x",               1, "%c",       'x')
    DO_TEST("%",               1, "%%")
    /* Mit %c kann man auch Nullbytes ausgeben */
    DO_TEST("\0",              1, "%c",       '\0')

    /* Vorzeichen erzwingen (Flag +) */
    DO_TEST("Hallo heimur",   12, "%+s",      "Hallo heimur")
    DO_TEST("+1024",           5, "%+d",      1024)
    DO_TEST("-1024",           5, "%+d",      -1024)
    DO_TEST("+1024",           5, "%+i",      1024)
    DO_TEST("-1024",           5, "%+i",      -1024)
    DO_TEST("1024",            4, "%+u",      1024u)
    DO_TEST("4294966272",     10, "%+u",      -1024u)
    DO_TEST("777",             3, "%+o",      0777u)
    DO_TEST("37777777001",    11, "%+o",      -0777u)
    DO_TEST("1234abcd",        8, "%+x",      0x1234abcdu)
    DO_TEST("edcb5433",        8, "%+x",      -0x1234abcdu)
    DO_TEST("1234ABCD",        8, "%+X",      0x1234abcdu)
    DO_TEST("EDCB5433",        8, "%+X",      -0x1234abcdu)
    DO_TEST("x",               1, "%+c",      'x')

    /* Vorzeichenplatzhalter erzwingen (Flag <space>) */
    DO_TEST("Hallo heimur",   12, "% s",      "Hallo heimur")
    DO_TEST(" 1024",           5, "% d",      1024)
    DO_TEST("-1024",           5, "% d",      -1024)
    DO_TEST(" 1024",           5, "% i",      1024)
    DO_TEST("-1024",           5, "% i",      -1024)
    DO_TEST("1024",            4, "% u",      1024u)
    DO_TEST("4294966272",     10, "% u",      -1024u)
    DO_TEST("777",             3, "% o",      0777u)
    DO_TEST("37777777001",    11, "% o",      -0777u)
    DO_TEST("1234abcd",        8, "% x",      0x1234abcdu)
    DO_TEST("edcb5433",        8, "% x",      -0x1234abcdu)
    DO_TEST("1234ABCD",        8, "% X",      0x1234abcdu)
    DO_TEST("EDCB5433",        8, "% X",      -0x1234abcdu)
    DO_TEST("x",               1, "% c",      'x')

    /* Flag + hat Vorrang über <space> */
    DO_TEST("Hallo heimur",   12, "%+ s",      "Hallo heimur")
    DO_TEST("+1024",           5, "%+ d",      1024)
    DO_TEST("-1024",           5, "%+ d",      -1024)
    DO_TEST("+1024",           5, "%+ i",      1024)
    DO_TEST("-1024",           5, "%+ i",      -1024)
    DO_TEST("1024",            4, "%+ u",      1024u)
    DO_TEST("4294966272",     10, "%+ u",      -1024u)
    DO_TEST("777",             3, "%+ o",      0777u)
    DO_TEST("37777777001",    11, "%+ o",      -0777u)
    DO_TEST("1234abcd",        8, "%+ x",      0x1234abcdu)
    DO_TEST("edcb5433",        8, "%+ x",      -0x1234abcdu)
    DO_TEST("1234ABCD",        8, "%+ X",      0x1234abcdu)
    DO_TEST("EDCB5433",        8, "%+ X",      -0x1234abcdu)
    DO_TEST("x",               1, "%+ c",      'x')

    /* Alternative Form */
    DO_TEST("0777",            4, "%#o",      0777u)
    DO_TEST("037777777001",   12, "%#o",      -0777u)
    DO_TEST("0x1234abcd",     10, "%#x",      0x1234abcdu)
    DO_TEST("0xedcb5433",     10, "%#x",      -0x1234abcdu)
    DO_TEST("0X1234ABCD",     10, "%#X",      0x1234abcdu)
    DO_TEST("0XEDCB5433",     10, "%#X",      -0x1234abcdu)
    DO_TEST("0",               1, "%#o",      0u)
    DO_TEST("0",               1, "%#x",      0u)
    DO_TEST("0",               1, "%#X",      0u)

    /* Feldbreite: Kleiner als Ausgabe */
    //DO_TEST("Hallo heimur",   12, "%1s",      "Hallo heimur")
    DO_TEST("1024",            4, "%1d",      1024)
    DO_TEST("-1024",           5, "%1d",      -1024)
    DO_TEST("1024",            4, "%1i",      1024)
    DO_TEST("-1024",           5, "%1i",      -1024)
    DO_TEST("1024",            4, "%1u",      1024u)
    DO_TEST("4294966272",     10, "%1u",      -1024u)
    DO_TEST("777",             3, "%1o",      0777u)
    DO_TEST("37777777001",    11, "%1o",      -0777u)
    DO_TEST("1234abcd",        8, "%1x",      0x1234abcdu)
    DO_TEST("edcb5433",        8, "%1x",      -0x1234abcdu)
    DO_TEST("1234ABCD",        8, "%1X",      0x1234abcdu)
    DO_TEST("EDCB5433",        8, "%1X",      -0x1234abcdu)
    DO_TEST("x",               1, "%1c",      'x')

    /* Feldbreite: Größer als Ausgabe */
    //DO_TEST("               Hallo",  20, "%20s",      "Hallo")
    DO_TEST("                1024",  20, "%20d",      1024)
    DO_TEST("               -1024",  20, "%20d",      -1024)
    DO_TEST("                1024",  20, "%20i",      1024)
    DO_TEST("               -1024",  20, "%20i",      -1024)
    DO_TEST("                1024",  20, "%20u",      1024u)
    DO_TEST("          4294966272",  20, "%20u",      -1024u)
    DO_TEST("                 777",  20, "%20o",      0777u)
    DO_TEST("         37777777001",  20, "%20o",      -0777u)
    DO_TEST("            1234abcd",  20, "%20x",      0x1234abcdu)
    DO_TEST("            edcb5433",  20, "%20x",      -0x1234abcdu)
    DO_TEST("            1234ABCD",  20, "%20X",      0x1234abcdu)
    DO_TEST("            EDCB5433",  20, "%20X",      -0x1234abcdu)
    DO_TEST("                   x",  20, "%20c",      'x')

    /* Feldbreite: Linksbündig */
    DO_TEST("Hallo               ",  20, "%-20s",      "Hallo")
    DO_TEST("1024                ",  20, "%-20d",      1024)
    DO_TEST("-1024               ",  20, "%-20d",      -1024)
    DO_TEST("1024                ",  20, "%-20i",      1024)
    DO_TEST("-1024               ",  20, "%-20i",      -1024)
    DO_TEST("1024                ",  20, "%-20u",      1024u)
    DO_TEST("4294966272          ",  20, "%-20u",      -1024u)
    DO_TEST("777                 ",  20, "%-20o",      0777u)
    DO_TEST("37777777001         ",  20, "%-20o",      -0777u)
    DO_TEST("1234abcd            ",  20, "%-20x",      0x1234abcdu)
    DO_TEST("edcb5433            ",  20, "%-20x",      -0x1234abcdu)
    DO_TEST("1234ABCD            ",  20, "%-20X",      0x1234abcdu)
    DO_TEST("EDCB5433            ",  20, "%-20X",      -0x1234abcdu)
    DO_TEST("x                   ",  20, "%-20c",      'x')

    /* Feldbreite: Padding mit 0 */
    DO_TEST("00000000000000001024",  20, "%020d",      1024)
    DO_TEST("-0000000000000001024",  20, "%020d",      -1024)
    DO_TEST("00000000000000001024",  20, "%020i",      1024)
    DO_TEST("-0000000000000001024",  20, "%020i",      -1024)
    DO_TEST("00000000000000001024",  20, "%020u",      1024u)
    DO_TEST("00000000004294966272",  20, "%020u",      -1024u)
    DO_TEST("00000000000000000777",  20, "%020o",      0777u)
    DO_TEST("00000000037777777001",  20, "%020o",      -0777u)

    DO_TEST("0000000000001234abcd",  20, "%020x",      0x1234abcdu)
    DO_TEST("000000000000edcb5433",  20, "%020x",      -0x1234abcdu)
    DO_TEST("0000000000001234ABCD",  20, "%020X",      0x1234abcdu)
    DO_TEST("000000000000EDCB5433",  20, "%020X",      -0x1234abcdu)

    /* Feldbreite: Padding und alternative Form */
    DO_TEST("                0777",  20, "%#20o",      0777u)
    DO_TEST("        037777777001",  20, "%#20o",      -0777u)
    DO_TEST("          0x1234abcd",  20, "%#20x",      0x1234abcdu)
    DO_TEST("          0xedcb5433",  20, "%#20x",      -0x1234abcdu)
    DO_TEST("          0X1234ABCD",  20, "%#20X",      0x1234abcdu)
    DO_TEST("          0XEDCB5433",  20, "%#20X",      -0x1234abcdu)

    DO_TEST("00000000000000000777",  20, "%#020o",     0777u)
    DO_TEST("00000000037777777001",  20, "%#020o",     -0777u)
    DO_TEST("0x00000000001234abcd",  20, "%#020x",     0x1234abcdu)
    DO_TEST("0x0000000000edcb5433",  20, "%#020x",     -0x1234abcdu)
    DO_TEST("0X00000000001234ABCD",  20, "%#020X",     0x1234abcdu)
    DO_TEST("0X0000000000EDCB5433",  20, "%#020X",     -0x1234abcdu)

    /* Feldbreite: - hat Vorrang vor 0 */
    DO_TEST("Hallo               ",  20, "%0-20s",      "Hallo")
    DO_TEST("1024                ",  20, "%0-20d",      1024)
    DO_TEST("-1024               ",  20, "%0-20d",      -1024)
    DO_TEST("1024                ",  20, "%0-20i",      1024)
    DO_TEST("-1024               ",  20, "%0-20i",      -1024)
    DO_TEST("1024                ",  20, "%0-20u",      1024u)
    DO_TEST("4294966272          ",  20, "%0-20u",      -1024u)
    DO_TEST("777                 ",  20, "%-020o",      0777u)
    DO_TEST("37777777001         ",  20, "%-020o",      -0777u)
    DO_TEST("1234abcd            ",  20, "%-020x",      0x1234abcdu)
    DO_TEST("edcb5433            ",  20, "%-020x",      -0x1234abcdu)
    DO_TEST("1234ABCD            ",  20, "%-020X",      0x1234abcdu)
    DO_TEST("EDCB5433            ",  20, "%-020X",      -0x1234abcdu)
    DO_TEST("x                   ",  20, "%-020c",      'x')

    /* Feldbreite: Aus Parameter */
    DO_TEST("               Hallo",  20, "%*s",      20, "Hallo")
    DO_TEST("                1024",  20, "%*d",      20, 1024)
    DO_TEST("               -1024",  20, "%*d",      20, -1024)
    DO_TEST("                1024",  20, "%*i",      20, 1024)
    DO_TEST("               -1024",  20, "%*i",      20, -1024)
    DO_TEST("                1024",  20, "%*u",      20, 1024u)
    DO_TEST("          4294966272",  20, "%*u",      20, -1024u)
    DO_TEST("                 777",  20, "%*o",      20, 0777u)
    DO_TEST("         37777777001",  20, "%*o",      20, -0777u)
    DO_TEST("            1234abcd",  20, "%*x",      20, 0x1234abcdu)
    DO_TEST("            edcb5433",  20, "%*x",      20, -0x1234abcdu)
    DO_TEST("            1234ABCD",  20, "%*X",      20, 0x1234abcdu)
    DO_TEST("            EDCB5433",  20, "%*X",      20, -0x1234abcdu)
    DO_TEST("                   x",  20, "%*c",      20, 'x')

    /* Präzision / Mindestanzahl von Ziffern */
    DO_TEST("Hallo heimur",           12, "%.20s",      "Hallo heimur")
    DO_TEST("00000000000000001024",   20, "%.20d",      1024)
    DO_TEST("-00000000000000001024",  21, "%.20d",      -1024)
    DO_TEST("00000000000000001024",   20, "%.20i",      1024)
    DO_TEST("-00000000000000001024",  21, "%.20i",      -1024)
    DO_TEST("00000000000000001024",   20, "%.20u",      1024u)
    DO_TEST("00000000004294966272",   20, "%.20u",      -1024u)
    DO_TEST("00000000000000000777",   20, "%.20o",      0777u)
    DO_TEST("00000000037777777001",   20, "%.20o",      -0777u)
    DO_TEST("0000000000001234abcd",   20, "%.20x",      0x1234abcdu)
    DO_TEST("000000000000edcb5433",   20, "%.20x",      -0x1234abcdu)
    DO_TEST("0000000000001234ABCD",   20, "%.20X",      0x1234abcdu)
    DO_TEST("000000000000EDCB5433",   20, "%.20X",      -0x1234abcdu)

    /* Feldbreite und Präzision */
    //DO_TEST("               Hallo",   20, "%20.5s",     "Hallo heimur")
    DO_TEST("               01024",   20, "%20.5d",      1024)
    DO_TEST("              -01024",   20, "%20.5d",      -1024)
    DO_TEST("               01024",   20, "%20.5i",      1024)
    DO_TEST("              -01024",   20, "%20.5i",      -1024)
    DO_TEST("               01024",   20, "%20.5u",      1024u)
    DO_TEST("          4294966272",   20, "%20.5u",      -1024u)
    DO_TEST("               00777",   20, "%20.5o",      0777u)
    DO_TEST("         37777777001",   20, "%20.5o",      -0777u)
    DO_TEST("            1234abcd",   20, "%20.5x",      0x1234abcdu)
    DO_TEST("          00edcb5433",   20, "%20.10x",     -0x1234abcdu)
    DO_TEST("            1234ABCD",   20, "%20.5X",      0x1234abcdu)
    DO_TEST("          00EDCB5433",   20, "%20.10X",     -0x1234abcdu)

    /* Präzision: 0 wird ignoriert */
    DO_TEST("               Hallo",   20, "%020.5s",    "Hallo heimur")
    DO_TEST("               01024",   20, "%020.5d",     1024)
    DO_TEST("              -01024",   20, "%020.5d",     -1024)
    DO_TEST("               01024",   20, "%020.5i",     1024)
    DO_TEST("              -01024",   20, "%020.5i",     -1024)
    DO_TEST("               01024",   20, "%020.5u",     1024u)
    DO_TEST("          4294966272",   20, "%020.5u",     -1024u)
    DO_TEST("               00777",   20, "%020.5o",     0777u)
    DO_TEST("         37777777001",   20, "%020.5o",     -0777u)
    DO_TEST("            1234abcd",   20, "%020.5x",     0x1234abcdu)
    DO_TEST("          00edcb5433",   20, "%020.10x",    -0x1234abcdu)
    DO_TEST("            1234ABCD",   20, "%020.5X",     0x1234abcdu)
    DO_TEST("          00EDCB5433",   20, "%020.10X",    -0x1234abcdu)

    /* Präzision 0 */
    DO_TEST("",                        0, "%.0s",        "Hallo heimur")
    DO_TEST("                    ",   20, "%20.0s",      "Hallo heimur")
    DO_TEST("",                        0, "%.s",         "Hallo heimur")
    DO_TEST("                    ",   20, "%20.s",       "Hallo heimur")
    DO_TEST("                1024",   20, "%20.0d",      1024)
    DO_TEST("               -1024",   20, "%20.d",       -1024)
    DO_TEST("                    ",   20, "%20.d",       0)
    DO_TEST("                1024",   20, "%20.0i",      1024)
    DO_TEST("               -1024",   20, "%20.i",       -1024)
    DO_TEST("                    ",   20, "%20.i",       0)
    DO_TEST("                1024",   20, "%20.u",       1024u)
    DO_TEST("          4294966272",   20, "%20.0u",      -1024u)
    DO_TEST("                    ",   20, "%20.u",       0u)

    DO_TEST("                 777",   20, "%20.o",       0777u)
    DO_TEST("         37777777001",   20, "%20.0o",      -0777u)
    DO_TEST("                    ",   20, "%20.o",       0u)
    DO_TEST("            1234abcd",   20, "%20.x",       0x1234abcdu)
    DO_TEST("            edcb5433",   20, "%20.0x",      -0x1234abcdu)
    DO_TEST("                    ",   20, "%20.x",       0u)
    DO_TEST("            1234ABCD",   20, "%20.X",       0x1234abcdu)
    DO_TEST("            EDCB5433",   20, "%20.0X",      -0x1234abcdu)
    DO_TEST("                    ",   20, "%20.X",       0u)

    /* Negative Präzision wird ignoriert */
    /* XXX glibc tut nicht, was ich erwartet habe, vorerst deaktiviert... */

    DO_TEST("Hallo heimur",   12, "%.-42s",       "Hallo heimur")
    DO_TEST("1024",            4, "%.-42d",       1024)
    DO_TEST("-1024",           5, "%.-42d",       -1024)
    DO_TEST("1024",            4, "%.-42i",       1024)
    DO_TEST("-1024",           5, "%.-42i",       -1024)
    DO_TEST("1024",            4, "%.-42u",       1024u)
    DO_TEST("4294966272",     10, "%.-42u",       -1024u)
    DO_TEST("777",             3, "%.-42o",       0777u)
    DO_TEST("37777777001",    11, "%.-42o",       -0777u)
    DO_TEST("1234abcd",        8, "%.-42x",       0x1234abcdu)
    DO_TEST("edcb5433",        8, "%.-42x",       -0x1234abcdu)
    DO_TEST("1234ABCD",        8, "%.-42X",       0x1234abcdu)
    DO_TEST("EDCB5433",        8, "%.-42X",       -0x1234abcdu)

    /*
     * Präzision und Feldbreite aus Parameter.
     * + hat Vorrang vor <space>, - hat Vorrang vor 0 (das eh ignoriert wird,
     * weil eine Präzision angegeben ist)
     */
    DO_TEST("Hallo               ",   20, "% -0+*.*s",    20,  5, "Hallo heimur")
    DO_TEST("+01024              ",   20, "% -0+*.*d",    20,  5,  1024)
    DO_TEST("-01024              ",   20, "% -0+*.*d",    20,  5,  -1024)
    DO_TEST("+01024              ",   20, "% -0+*.*i",    20,  5,  1024)
    DO_TEST("-01024              ",   20, "% 0-+*.*i",    20,  5,  -1024)
    DO_TEST("01024               ",   20, "% 0-+*.*u",    20,  5,  1024u)
    DO_TEST("4294966272          ",   20, "% 0-+*.*u",    20,  5,  -1024u)
    DO_TEST("00777               ",   20, "%+ -0*.*o",    20,  5,  0777u)
    DO_TEST("37777777001         ",   20, "%+ -0*.*o",    20,  5,  -0777u)
    DO_TEST("1234abcd            ",   20, "%+ -0*.*x",    20,  5,  0x1234abcdu)
    DO_TEST("00edcb5433          ",   20, "%+ -0*.*x",    20, 10,  -0x1234abcdu)
    DO_TEST("1234ABCD            ",   20, "% -+0*.*X",    20,  5,  0x1234abcdu)
    DO_TEST("00EDCB5433          ",   20, "% -+0*.*X",    20, 10,  -0x1234abcdu)

}

//===-- Unittests for snprintf --------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
// The sprintf test cases cover testing the shared printf functionality, so
// these tests will focus on snprintf exclusive features.

TEST(LlvmLibcSNPrintfTest, CutOff) {
    char buff[64];
    int written;

    written =
        __MACONDO_TEST_NAMESPACE::snprintf(buff, 16, "A simple string with no conversions.");
    EXPECT_EQ(written, 15);
    ASSERT_STREQ(buff, "A simple string");

    written = __MACONDO_TEST_NAMESPACE::snprintf(buff, 5, "%s", "1234567890");
    EXPECT_EQ(written, 4);
    ASSERT_STREQ(buff, "1234");

    // passing null as the output pointer is allowed as long as buffsz is 0.
    written = __MACONDO_TEST_NAMESPACE::snprintf(nullptr, 0, "%s and more", "1234567890");
    EXPECT_EQ(written, 0);
}

TEST(LlvmLibcSNPrintfTest, NoCutOff) {
    char buff[64];
    int written;

    written =
        __MACONDO_TEST_NAMESPACE::snprintf(buff, 37, "A simple string with no conversions.");
    EXPECT_EQ(written, 36);
    ASSERT_STREQ(buff, "A simple string with no conversions.");

    written = __MACONDO_TEST_NAMESPACE::snprintf(buff, 20, "%s", "1234567890");
    EXPECT_EQ(written, 10);
    ASSERT_STREQ(buff, "1234567890");
}

TEST(LlvmLibcSPrintfTest, SimpleNoConv) {
    char buff[64];
    int written;

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "A simple string with no conversions.");
    EXPECT_EQ(written, 36);
    ASSERT_STREQ(buff, "A simple string with no conversions.");
}

TEST(LlvmLibcSPrintfTest, PercentConv) {
    char buff[64];
    int written;

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%%");
    EXPECT_EQ(written, 1);
    ASSERT_STREQ(buff, "%");

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "abc %% def");
    EXPECT_EQ(written, 9);
    ASSERT_STREQ(buff, "abc % def");

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%%%%%%");
    EXPECT_EQ(written, 3);
    ASSERT_STREQ(buff, "%%%");
}

TEST(LlvmLibcSPrintfTest, CharConv) {
    char buff[64];
    int written;

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%c", 'a');
    EXPECT_EQ(written, 1);
    ASSERT_STREQ(buff, "a");

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%3c %-3c", '1', '2');
    EXPECT_EQ(written, 7);
    ASSERT_STREQ(buff, "  1 2  ");

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%*c", 2, '3');
    EXPECT_EQ(written, 2);
    ASSERT_STREQ(buff, " 3");
}

TEST(LlvmLibcSPrintfTest, StringConv) {
    char buff[64];
    int written;

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%s", "abcDEF123");
    EXPECT_EQ(written, 9);
    ASSERT_STREQ(buff, "abcDEF123");

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%10s %-10s", "centered", "title");
    EXPECT_EQ(written, 21);
    ASSERT_STREQ(buff, "  centered title     ");

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%-5.4s%-4.4s", "words can describe",
                                   "soups most delicious");
    EXPECT_EQ(written, 9);
    ASSERT_STREQ(buff, "word soup");

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%*s %.*s %*.*s", 10, "beginning", 2,
                                   "isn't", 12, 10, "important. Ever.");
    EXPECT_EQ(written, 26);
    ASSERT_STREQ(buff, " beginning is   important.");
}

TEST(LlvmLibcSPrintfTest, IntConv) {
    char buff[64];
    int written;

    // Basic Tests.

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%d", 123);
    EXPECT_EQ(written, 3);
    ASSERT_STREQ(buff, "123");

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%i", -456);
    EXPECT_EQ(written, 4);
    ASSERT_STREQ(buff, "-456");

    // Length Modifier Tests.

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%hhu", 257); // 0x101
    EXPECT_EQ(written, 1);
    ASSERT_STREQ(buff, "1");

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%llu", 18446744073709551615ull);
    EXPECT_EQ(written, 20);
    ASSERT_STREQ(buff, "18446744073709551615"); // ull max

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%tu", ~ptrdiff_t(0));
    if (sizeof(ptrdiff_t) == 8) {
        EXPECT_EQ(written, 20);
        ASSERT_STREQ(buff, "18446744073709551615");
    } else if (sizeof(ptrdiff_t) == 4) {
        EXPECT_EQ(written, 10);
        ASSERT_STREQ(buff, "4294967296");
    }

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%lld", -9223372036854775807ll - 1ll);
    EXPECT_EQ(written, 20);
    ASSERT_STREQ(buff, "-9223372036854775808"); // ll min

    // Min Width Tests.

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%4d", 789);
    EXPECT_EQ(written, 4);
    ASSERT_STREQ(buff, " 789");

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%2d", 987);
    EXPECT_EQ(written, 3);
    ASSERT_STREQ(buff, "987");

    // Precision Tests.

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%d", 0);
    EXPECT_EQ(written, 1);
    ASSERT_STREQ(buff, "0");

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%.0d", 0);
    EXPECT_EQ(written, 0);
    ASSERT_STREQ(buff, "");

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%.5d", 654);
    EXPECT_EQ(written, 5);
    ASSERT_STREQ(buff, "00654");

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%.5d", -321);
    EXPECT_EQ(written, 6);
    ASSERT_STREQ(buff, "-00321");

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%.2d", 135);
    EXPECT_EQ(written, 3);
    ASSERT_STREQ(buff, "135");

    // Flag Tests.

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%.5d", -321);
    EXPECT_EQ(written, 6);
    ASSERT_STREQ(buff, "-00321");

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%-5d", 246);
    EXPECT_EQ(written, 5);
    ASSERT_STREQ(buff, "246  ");

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%-5d", -147);
    EXPECT_EQ(written, 5);
    ASSERT_STREQ(buff, "-147 ");

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%+d", 258);
    EXPECT_EQ(written, 4);
    ASSERT_STREQ(buff, "+258");

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "% d", 369);
    EXPECT_EQ(written, 4);
    ASSERT_STREQ(buff, " 369");

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%05d", 470);
    EXPECT_EQ(written, 5);
    ASSERT_STREQ(buff, "00470");

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%05d", -581);
    EXPECT_EQ(written, 5);
    ASSERT_STREQ(buff, "-0581");

    // Combined Tests.

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%+ u", 692);
    EXPECT_EQ(written, 3);
    ASSERT_STREQ(buff, "692");

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%+ -05d", 703);
    EXPECT_EQ(written, 5);
    ASSERT_STREQ(buff, "+703 ");

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%7.5d", 814);
    EXPECT_EQ(written, 7);
    ASSERT_STREQ(buff, "  00814");

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%7.5d", -925);
    EXPECT_EQ(written, 7);
    ASSERT_STREQ(buff, " -00925");

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%7.5d", 159);
    EXPECT_EQ(written, 7);
    ASSERT_STREQ(buff, "  00159");

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "% -7.5d", 260);
    EXPECT_EQ(written, 7);
    ASSERT_STREQ(buff, " 00260 ");

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%5.4d", 10000);
    EXPECT_EQ(written, 5);
    ASSERT_STREQ(buff, "10000");

    // Multiple Conversion Tests.

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%10d %-10d", 456, -789);
    EXPECT_EQ(written, 21);
    ASSERT_STREQ(buff, "       456 -789      ");

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "%-5.4d%+.4u", 75, 25);
    EXPECT_EQ(written, 9);
    ASSERT_STREQ(buff, "0075 0025");

    written = __MACONDO_TEST_NAMESPACE::sprintf(buff, "% 05hhi %+-0.5llu %-+ 06.3zd",
                                   256 + 127, 68719476736ll, size_t(2));
    EXPECT_EQ(written, 24);
    ASSERT_STREQ(buff, " 0127 68719476736 +002  ");
}

// Here is my tests

TEST(MacondoLibcSnprintfTest, StringParameters) {
    char buffer[BUFFER_SIZE];
    int res = __MACONDO_TEST_NAMESPACE::snprintf(buffer, BUFFER_SIZE, "%s", "Hallo heimur");
    ASSERT_EQ(res, strlen("Hallo heimur"));
    ASSERT_STREQ("Hallo heimur", buffer);
}

TEST(MacondoLibcSnprintfTest, NullParameters) {
    char buffer[BUFFER_SIZE];
    int res = __MACONDO_TEST_NAMESPACE::snprintf(buffer, BUFFER_SIZE, "%s", NULL);
    ASSERT_EQ(res, strlen(kNull));
    ASSERT_STREQ("(null)", buffer);

    res = __MACONDO_TEST_NAMESPACE::snprintf(buffer, BUFFER_SIZE, "%p", NULL);
    ASSERT_EQ(res, strlen(kNil));
    ASSERT_STREQ("(nil)", buffer);
}

TEST(MacondoLibcSnprintfTest, Range) {
    char buffer[BUFFER_SIZE];
    size_t null_len = strlen(kNull);
    int res = -1;

    for (size_t i = 1; i < null_len; i++) {
        res = __MACONDO_TEST_NAMESPACE::snprintf(buffer, i, "%s", NULL);

        if (i > 1) {
            ASSERT_EQ(res, i - 1);
            ASSERT_EQ(0, memcmp(buffer, kNull, i - 1));
        } else {
            ASSERT_EQ(res, 0);
        }
    }
}