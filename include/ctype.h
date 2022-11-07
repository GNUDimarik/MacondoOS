#pragma once

#include "defs.h"

__MACONDO_TEST_NAMESPACE_BEGIN
__BEGIN_DECLS

/**
 * @defgroup ctype ctype routines
 * @ingroup  stdlib
 * @{
 */

/**
 * @brief   toascii - translate an integer to a 7-bit ASCII character
 * @param c         - integer for converting
 * @return          - c & 0x7f
 */
int toascii(int c);

/**
 * @brief isacii - function tests whether c is a 7-bit US-ASCII character code.
 * @param c - character to test
 * @return non-zero if c is a 7-bit US-ASCII character code between 0 and octal 0177 inclusive; otherwise, it returns 0
 */
int isascii(int c);

/**
 * @brief   isalnum - checks if a character is alphanumeric
 * @param c - character to test
 * @return true if a character is alphanumeric and false otherwise
 */
int isalnum(int c);

/**
 * @brief isalpha - checks if a character is alphabetic
 * @param c - character to test
 * @return true if a character is alphabetic and false otherwise
 */
int isalpha(int c);
/**
 * @brief  isblank - checks if a character is a blank character
 * @param  c - character to test
 * @return true if a character is a blank character and false otherwise
 */
int isblank(int c);

/**
 * @brief iscntrl - checks if a character is a control character
 * @param c - character to test
 * @return true if a character is a control character and false otherwise
 */
int iscntrl(int c);

/**
 * @brief isdigit - checks if a character is a digit
 * @param c - character to test
 * @return true if a character is a digit and false otherwise
 */
int isdigit(int c);

/**
 * @brief isgraph - checks if a character is a graphical character
 * @param c - character to test
 * @return true if a character is a graphical character and false otherwise
 */
int isgraph(int c);

/**
 * @brief islower - checks if a character is lowercase
 * @param c - character to test
 * @return true if a character is lowercase and false otherwise
 */
int islower(int c);
/**
 * @brief isprint - checks if a character is a printing character
 * @param c - character to test
 * @return true if a character is a printing character and false otherwise
 */
int isprint(int c);

/**
 * @brief  ispunct - checks if a character is a punctuation character
 * @param  c - character to test
 * @return true if a character is a punctuation character and false otherwise
 */
int ispunct(int c);

/**
 * @brief isspace - checks if a character is a space character
 * @param c - character to test
 * @return true if a character is a space character and false otherwise
 */
int isspace(int c);

/**
 * @brief  isupper - checks if a character is an uppercase character
 * @param  c - character to test
 * @return true if a character is an uppercase character and false otherwise
 */
int isupper(int c);

/**
 * @brief  isxdigit - checks if a character is a hexadecimal character
 * @param  c - character to test
 * @return true if a character is a hexadecimal character and false otherwise
 */
int isxdigit(int c);

/**
 * @brief  tolower - converts a character to lowercase
 * @param  c - character to test
 * @return converted a character to lowercase
 */
int tolower(int c);

/**
 * @brief  toupper - converts a character to uppercase
 * @param  c - character to test
 * @return converted a character to uppercase
 */
int toupper(int c);

__END_DECLS
__MACONDO_TEST_NAMESPACE_END

/** @} */