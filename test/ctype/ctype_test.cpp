//===-- Unittests for ctype----------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
#include <gtest/gtest.h>

/**
 * These tests ported from LLVM
 * */

#define  __TEST_DRIVEN__
#include <ctype.hpp>

TEST(LlvmLibcIsAlNum, DefaultLocale)
{
// Loops through all characters, verifying that numbers and letters
// return non-zero integer and everything else returns a zero.
    for (int c = 0; c < 255; ++c) {
        if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') ||
            ('0' <= c && c <= '9'))
            EXPECT_NE(__STD_NAMESPACE::isalnum(c), 0);
        else
            EXPECT_EQ(__STD_NAMESPACE::isalnum(c), 0);
    }
}

TEST(LlvmLibcIsAlpha, DefaultLocale) {
    // Loops through all characters, verifying that letters return a
    // non-zero integer and everything else returns zero.
    for (int ch = 0; ch < 255; ++ch) {
        if (('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z'))
            EXPECT_NE(__STD_NAMESPACE::isalpha(ch), 0);
        else
            EXPECT_EQ(__STD_NAMESPACE::isalpha(ch), 0);
    }
}

TEST(LlvmLibcIsAscii, DefaultLocale) {
    // Loops through all characters, verifying that ascii characters
    //    (which are all 7 bit unsigned integers)
    // return a non-zero integer and everything else returns zero.
    for (int ch = 0; ch < 255; ++ch) {
        if (ch <= 0x7f)
            EXPECT_NE(__STD_NAMESPACE::isascii(ch), 0);
        else
            EXPECT_EQ(__STD_NAMESPACE::isascii(ch), 0);
    }
}

TEST(LlvmLibcIsBlank, DefaultLocale) {
    // Loops through all characters, verifying that space and horizontal tab
    // return a non-zero integer and everything else returns zero.
    for (int ch = 0; ch < 255; ++ch) {
        if (ch == ' ' || ch == '\t')
            EXPECT_NE(__STD_NAMESPACE::isblank(ch), 0);
        else
            EXPECT_EQ(__STD_NAMESPACE::isblank(ch), 0);
    }
}

TEST(LlvmLibcIsCntrl, DefaultLocale) {
    // Loops through all characters, verifying that control characters
    // return a non-zero integer, all others return zero.
    for (int ch = 0; ch < 255; ++ch) {
        if ((0 <= ch && ch <= 0x1f /*US*/) || ch == 0x7f /*DEL*/)
            EXPECT_NE(__STD_NAMESPACE::iscntrl(ch), 0);
        else
            EXPECT_EQ(__STD_NAMESPACE::iscntrl(ch), 0);
    }
}

TEST(LlvmLibcIsDigit, DefaultLocale) {
    // Loops through all characters, verifying that numbers return a
    // non-zero integer and everything else returns zero.
    for (int ch = 0; ch < 255; ++ch) {
        if ('0' <= ch && ch <= '9')
            EXPECT_NE(__STD_NAMESPACE::isdigit(ch), 0);
        else
            EXPECT_EQ(__STD_NAMESPACE::isdigit(ch), 0);
    }
}

TEST(LlvmLibcIsGraph, DefaultLocale) {
    // Loops through all characters, verifying that graphical characters
    // return a non-zero integer, everything else returns zero.
    for (int ch = 0; ch < 255; ++ch) {
        if ('!' <= ch && ch <= '~') // A-Z, a-z, 0-9, punctuation.
            EXPECT_NE(__STD_NAMESPACE::isgraph(ch), 0);
        else
            EXPECT_EQ(__STD_NAMESPACE::isgraph(ch), 0);
    }
}

TEST(LlvmLibcIsLower, DefaultLocale) {
    // Loops through all characters, verifying that lowercase letters
    // return a non-zero integer and everything else returns zero.
    for (int ch = 0; ch < 255; ++ch) {
        if ('a' <= ch && ch <= 'z')
            EXPECT_NE(__STD_NAMESPACE::islower(ch), 0);
        else
            EXPECT_EQ(__STD_NAMESPACE::islower(ch), 0);
    }
}

TEST(LlvmLibcIsPrint, DefaultLocale) {
    for (int ch = 0; ch < 255; ++ch) {
        if (' ' <= ch && ch <= '~') // A-Z, a-z, 0-9, punctuation, space.
            EXPECT_NE(__STD_NAMESPACE::isprint(ch), 0);
        else
            EXPECT_EQ(__STD_NAMESPACE::isprint(ch), 0);
    }
}

// Helper function to mark the sections of the ASCII table that are
// punctuation characters. These are listed below:
//  Decimal    |         Symbol
//  -----------------------------------------
//  33 -  47   |  ! " $ % & ' ( ) * + , - . /
//  58 -  64   |  : ; < = > ? @
//  91 -  96   |  [ \ ] ^ _ `
// 123 - 126   |  { | } ~
static inline int is_punctuation_character(int c) {
    return ('!' <= c && c <= '/') || (':' <= c && c <= '@') ||
        ('[' <= c && c <= '`') || ('{' <= c && c <= '~');
}

TEST(LlvmLibcIsPunct, DefaultLocale) {
    // Loops through all characters, verifying that punctuation characters
    // return a non-zero integer, and everything else returns zero.
    for (int ch = 0; ch < 255; ++ch) {
        if (is_punctuation_character(ch))
            EXPECT_NE(__STD_NAMESPACE::ispunct(ch), 0);
        else
            EXPECT_EQ(__STD_NAMESPACE::ispunct(ch), 0);
    }
}

TEST(LlvmLibcIsSpace, DefaultLocale) {
    // Loops through all characters, verifying that space characters
    // return true and everything else returns false.
    // Hexadecimal | Symbol
    // ---------------------------
    //    0x09     |   horizontal tab
    //    0x0a     |   line feed
    //    0x0b     |   vertical tab
    //    0x0d     |   carriage return
    //    0x20     |   space
    for (int ch = 0; ch < 255; ++ch) {
        if (ch == 0x20 || (0x09 <= ch && ch <= 0x0d))
            EXPECT_NE(__STD_NAMESPACE::isspace(ch), 0);
        else
            EXPECT_EQ(__STD_NAMESPACE::isspace(ch), 0);
    }
}

TEST(LlvmLibcIsUpper, DefaultLocale) {
    // Loops through all characters, verifying that uppercase letters
    // return a non-zero integer and everything else returns zero.
    for (int ch = 0; ch < 255; ++ch) {
        if ('A' <= ch && ch <= 'Z')
            EXPECT_NE(__STD_NAMESPACE::isupper(ch), 0);
        else
            EXPECT_EQ(__STD_NAMESPACE::isupper(ch), 0);
    }
}

TEST(LlvmLibcIsXDigit, DefaultLocale) {
    for (int ch = 0; ch < 255; ++ch) {
        if (('0' <= ch && ch <= '9') || ('a' <= ch && ch <= 'f') ||
            ('A' <= ch && ch <= 'F'))
            EXPECT_NE(__STD_NAMESPACE::isxdigit(ch), 0);
        else
            EXPECT_EQ(__STD_NAMESPACE::isxdigit(ch), 0);
    }
}

TEST(LlvmLibcToLower, DefaultLocale) {
    for (int ch = 0; ch < 255; ++ch) {
        // This follows pattern 'A' + 32 = 'a'.
        if ('A' <= ch && ch <= 'Z')
            EXPECT_EQ(__STD_NAMESPACE::tolower(ch), ch + 32);
        else
            EXPECT_EQ(__STD_NAMESPACE::tolower(ch), ch);
    }
}

TEST(LlvmLibcToUpper, DefaultLocale) {
    for (int ch = 0; ch < 255; ++ch) {
        // This follows pattern 'a' - 32 = 'A'.
        if ('a' <= ch && ch <= 'z')
            EXPECT_EQ(__STD_NAMESPACE::toupper(ch), ch - 32);
        else
            EXPECT_EQ(__STD_NAMESPACE::toupper(ch), ch);
    }
}