#pragma once

#include "macondo/defs.h"

__STD_BEGIN_NAMESPACE
__BEGIN_DECLS

/**
 * @defgroup strings ctype routines
 * @ingroup  stdlib
 * @{
 */

/**
 * @brief isacii - function tests whether c is a 7-bit US-ASCII character code.
 * @param c - character to test
 * @return non-zero if c is a 7-bit US-ASCII character code between 0 and octal 0177 inclusive; otherwise, it returns 0
 */
static inline int isascii(int c)
{
    return c >= 0 && c <= 127;
}

/**
 * @brief   isalnum - checks if a character is alphanumeric
 * @param c - character to test
 * @return true if a character is alphanumeric and false otherwise
 */
static inline int isalnum(int c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

/**
 * @brief isalpha - checks if a character is alphabetic
 * @param c - character to test
 * @return true if a character is alphabetic and false otherwise
 */
static inline int isalpha(int c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

/**
 * @brief  isblank - checks if a character is a blank character
 * @param  c - character to test
 * @return true if a character is a blank character and false otherwise
 */
static inline int isblank(int c)
{
    return c == 9 || c == 32;
}

/**
 * @brief iscntrl - checks if a character is a control character
 * @param c - character to test
 * @return true if a character is a control character and false otherwise
 */
static inline int iscntrl(int c)
{
    return (c >= 0 && c <= 31) || c == 127;
}

/**
 * @brief isdigit - checks if a character is a digit
 * @param c - character to test
 * @return true if a character is a digit and false otherwise
 */
static inline int isdigit(int c)
{
    return c >= '0' && c <= '9';
}

/**
 * @brief isgraph - checks if a character is a graphical character
 * @param c - character to test
 * @return true if a character is a graphical character and false otherwise
 */
static inline int isgraph(int c)
{
    return c >= 33 && c <= 126;
}

/**
 * @brief islower - checks if a character is lowercase
 * @param c - character to test
 * @return true if a character is lowercase and false otherwise
 */
static inline int islower(int c)
{
    return c >= 'a' && c <= 'z';
}

/**
 * @brief isprint - checks if a character is a printing character
 * @param c - character to test
 * @return true if a character is a printing character and false otherwise
 */
static inline int isprint(int c)
{
    return c >= 32 && c <= 126;
}

/**
 * @brief  ispunct - checks if a character is a punctuation character
 * @param  c - character to test
 * @return true if a character is a punctuation character and false otherwise
 */
static inline int ispunct(int c)
{
    return (c >= 33 && c <= 47) || (c >= 58 && c <= 64)
        || (c >= 91 && c <= 96) || (c >= 123 && c <= 126);
}

/**
 * @brief isspace - checks if a character is a space character
 * @param c - character to test
 * @return true if a character is a space character and false otherwise
 */
static inline int isspace(int c)
{
    return (c >= 9 && c <= 13) || c == 32;
}

/**
 * @brief  isupper - checks if a character is an uppercase character
 * @param  c - character to test
 * @return true if a character is an uppercase character and false otherwise
 */
static inline int isupper(int c)
{
    return c >= 'A' && c <= 'Z';
}

/**
 * @brief  isxdigit - checks if a character is a hexadecimal character
 * @param  c - character to test
 * @return true if a character is a hexadecimal character and false otherwise
 */
static inline int isxdigit(int c)
{
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

/**
 * @brief  tolower - converts a character to lowercase
 * @param  c - character to test
 * @return converted a character to lowercase
 */
static inline int tolower(int c)
{
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    }

    return c;
}

/**
 * @brief  toupper - converts a character to uppercase
 * @param  c - character to test
 * @return converted a character to uppercase
 */
static inline int toupper(int c)
{
    if (c >= 'a' && c <= 'z') {
        return c - ('a' - 'A');
    }

    return c;
}

__END_DECLS
__STD_END_NAMESPACE

/** @} */