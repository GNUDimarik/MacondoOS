#ifndef MACONDOOS_INCLUDE_MACONDO_STDIO_H_
#define MACONDOOS_INCLUDE_MACONDO_STDIO_H_

#include "../defs.h"
#include <stdarg.h>
#include <stddef.h>

__BEGIN_DECLS
__MACONDO_TEST_NAMESPACE_BEGIN

int vsnprintf(char *buf, size_t size, const char *fmt, va_list ap);
int snprintf(char *buffer, size_t size, const char *fmt, ...);

__MACONDO_TEST_NAMESPACE_END
__END_DECLS

#endif //MACONDOOS_INCLUDE_MACONDO_STDIO_H_