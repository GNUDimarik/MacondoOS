#pragma once

#include "defs.h"
#include <stddef.h>


__BEGIN_DECLS
__STD_BEGIN_NAMESPACE

/**
 * @brief bzero - sets n bytes in s to zero
 * @param s     - pointer to region zeroize to
 * @param n     - number of bytes to zeroize
 */
void bzero(void *s, size_t n);

/// TODO: write documentation
size_t strlcpy(char *dst, const char *src, size_t size);

void bcopy(const void *src, void *dest, size_t size);

__END_DECLS
__STD_END_NAMESPACE
/** @} */