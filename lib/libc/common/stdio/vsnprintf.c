#include <stdarg.h>
#include <stddef.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <stdint.h>

#define MAX_NUMBER_LEN 64
#define HEX_BASE_SPECIFIER_INDEX 33

enum {
    kFormatFlagAlternateForm = 1,
    kFormatFlagZeroPad = 1 << 1,
    kFormatFlagAlignLeft = 1 << 2,
    kFormatFlagSign = 1 << 3,
    kFormatFlagSpace = 1 << 4,
    kFormatFlagHugeNumbers = 1 << 5,
    kFormatSignedValue = 1 << 8,
};

enum {
    kSizeSpecifier_l = 1,
    kSizeSpecifier_ll,
    kSizeSpecifier_hh,
    kSizeSpecifier_h,
    kSizeSpecifier_j,
    kSizeSpecifier_z,
    kSizeSpecifier_t,
    kSizeSpecifier_L
};

struct format_context_t {
    size_t precision;
    size_t field_width;
    size_t size_specifier;
    size_t flags;
    int sign;
    int radix;
};

/* Parses number and moves pointer to first non digit character */
static int parse_number(const char **str) {
    int result = 0;

    while (isdigit(**str)) {
        result = result * 10 + *((*str)++) - '0';
    }

    return result;
}

static char *do_ulltoa(unsigned long long number, int base,
                       char *buf, size_t buffer_size, const char *characters, size_t *size) {
    size_t i = 0;

    if (number != 0) {
        while (number != 0 && buffer_size-- > i) {
            long long n = number % base;
            number /= base;
            buf[i++] = characters[n];
        }
    } else {
        buf[i] = '0';
        i++;
    }

    buf[i] = '\0';
    *size = i;

    return strrev(buf);
}

static char *format_unsigned(char *buffer, unsigned long long number, struct format_context_t *ctx,
                             size_t max_size, size_t *out_len) {
    if (ctx->precision > max_size || ctx->field_width > max_size) {
        return NULL;
    }

    const char *characters = ctx->flags & kFormatFlagHugeNumbers
                             ? "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                             : "0123456789abcdefghijklmnopqrstuvwxyz";
    char digits[MAX_NUMBER_LEN];
    char *numbers = digits;
    char pad = ctx->flags & kFormatFlagZeroPad ? '0' : ' ';
    size_t number_len = 0;
    size_t size = 0;
    size_t i = 0;

    bzero(numbers, MAX_NUMBER_LEN);

    if (!ctx->sign && (ctx->flags & kFormatFlagSign)) {
        ctx->sign = '+';
    }

    if (!ctx->sign && (ctx->flags & kFormatFlagSpace)) {
        ctx->sign = ' ';
    }

    if (ctx->sign && !(ctx->flags & kFormatFlagAlternateForm) && ctx->field_width > 0) {
        --ctx->field_width;
    }

    numbers = do_ulltoa(number, ctx->radix, numbers, MAX_NUMBER_LEN, characters, &number_len);

    if (ctx->precision > 0 && ctx->field_width >= ctx->precision) {
        ctx->field_width -= ctx->precision;
    } else if (ctx->field_width >= number_len) {
        ctx->field_width -= number_len;
    }

    if ((ctx->flags & kFormatFlagAlternateForm)) {
        if (ctx->radix == 8 && ctx->field_width > 0) {
            ctx->field_width -= 1;
        } else if (ctx->field_width > 1) {
            ctx->field_width -= 2;
        }
    }

    if (!(ctx->flags & kFormatFlagAlignLeft)) {
        for (; ctx->field_width > 0 && size < max_size; ctx->field_width--, size++) {
            *buffer++ = pad;
        }
    }

    if (ctx->sign && !(ctx->flags & kFormatFlagAlternateForm) && size++ < max_size) {
        *buffer++ = ctx->sign;
    }

    if ((ctx->flags & kFormatFlagAlternateForm) && size++ < max_size) {
        if (ctx->radix == 8) {
            *buffer++ = 'o';
        } else if (ctx->radix == 16) {
            *buffer++ = '0';
            *buffer++ = characters[HEX_BASE_SPECIFIER_INDEX];
        }
    }

    if (ctx->precision >= number_len) {
        ctx->precision -= number_len;
    } else {
        ctx->precision = 0;
    }

    for (; ctx->precision > 0 && size < max_size; ctx->precision--, size++) {
        *buffer++ = '0';
    }

    for (i = 0; i < number_len && size < max_size; i++, size++) {
        *buffer++ = numbers[i];
    }

    for (; ctx->field_width > 0 && size < max_size; ctx->field_width--, size++) {
        *buffer++ = ' ';
    }

    *out_len = size;
    *buffer = '\0';
    return buffer;
}

static char *format_signed(char *buffer, long long number, struct format_context_t *ctx,
                           size_t max_size, size_t *number_len) {
    if (number < 0) {
        number = -number;
        ctx->sign = '-';
    }

    return format_unsigned(buffer, number, ctx, max_size, number_len);
}

static char *process_number(char *buffer, struct format_context_t *ctx, va_list ap,
                            size_t max_size, size_t *number_len) {
    long long ll_val = 0;
    unsigned long long ull_val = 0;

    switch (ctx->size_specifier) {
        case kSizeSpecifier_l:
            if (ctx->flags & kFormatSignedValue) {
                ll_val = va_arg(ap, int);
            } else {
                ull_val = va_arg(ap, unsigned int);
            }
            break;

        case kSizeSpecifier_ll:
            if (ctx->flags & kFormatSignedValue) {
                ll_val = va_arg(ap, long long);
            } else {
                ull_val = va_arg(ap, unsigned long long);
            }
            break;

        case kSizeSpecifier_L:
            if (ctx->flags & kFormatSignedValue) {
                ll_val = va_arg(ap, long long);
            } else {
                ull_val = va_arg(ap, unsigned long long);
            }
            break;

        case kSizeSpecifier_hh:
            if (ctx->flags & kFormatSignedValue) {
                ll_val = (char) va_arg(ap, int);
            } else {
                ull_val = (unsigned char) va_arg(ap, unsigned int);
            }
            break;

        case kSizeSpecifier_h:
            if (ctx->flags & kFormatSignedValue) {
                ll_val = (short) va_arg(ap, int);
            } else {
                ull_val = (unsigned short) va_arg(ap, unsigned int);
            }
            break;

        case kSizeSpecifier_z:ull_val = va_arg(ap, size_t);
            ctx->flags &= ~kFormatSignedValue;
            break;

        case kSizeSpecifier_t:ull_val = va_arg(ap, ptrdiff_t);
            ctx->flags &= ~kFormatSignedValue;
            break;

        case kSizeSpecifier_j:
            if (ctx->flags & kFormatSignedValue) {
                ll_val = va_arg(ap, intmax_t);
            } else {
                ull_val = va_arg(ap, uintmax_t);
            }
            break;

        default:
            if (ctx->flags & kFormatSignedValue) {
                ll_val = va_arg(ap, int);
            } else {
                ull_val = va_arg(ap, unsigned int);
            }
            break;

    }

    if (ctx->flags & kFormatSignedValue) {
        return format_signed(buffer, ll_val, ctx, max_size, number_len);
    }

    return format_unsigned(buffer, ull_val, ctx, max_size, number_len);
}

/**
 * @brief vsnprintf - produce output according to a format as described below
 * @param buf       - output buffer where formatted string returns
 * @param size      - size of buffer
 * @param fmt       - format string, supported specifiers are described bellow
 * @param ap        - va_list with arguments. Caller needs to call va_start before call of vsnprintf
 * @return          - length of formatted string or -1 if error occurred
 *
 * Supported conversion modifiers:
 *
 * X -
 * x -
 * i -
 * d -
 * o -
 * s -
 * p -
 * n -
 *
 * Supported size modifiers:
 *
 * hh -
 * h  -
 * L  -
 * ll -
 * l  -
 * z  -
 * t  -
 * j  -
 */

int vsnprintf(char *buf, size_t size, const char *fmt, va_list ap) {
    if (size > 1 && buf != NULL && fmt != NULL) {
        char *p_buf = buf;
        size_t sz = 0;
        struct format_context_t fmt_ctx;

        for (sz = 0; sz < size && *fmt != '\0'; ++sz, ++fmt) {
            if (*fmt != '%') {
                *p_buf++ = *fmt;
                continue;
            }

            fmt_ctx.flags = 0;
            /* handle format flags */
            while (*fmt++ != '\0') {
                switch (*fmt) {
                    case '#':fmt_ctx.flags |= kFormatFlagAlternateForm;
                        continue;

                    case ' ':fmt_ctx.flags |= kFormatFlagSpace;
                        fmt_ctx.flags &= ~kFormatFlagZeroPad;
                        continue;

                    case '0':fmt_ctx.flags |= kFormatFlagZeroPad;
                        continue;

                    case '-':fmt_ctx.flags |= kFormatFlagAlignLeft;
                        continue;

                    case '+':fmt_ctx.flags |= kFormatFlagSign;
                        fmt_ctx.flags &= ~kFormatFlagSpace;
                        continue;

                    default:break;
                }

                break;
            }

            fmt_ctx.field_width = 0;
            /* handle field width */
            if (isdigit(*fmt)) {
                fmt_ctx.field_width = parse_number(&fmt);
            } else if (*fmt == '*') {
                ++fmt;

                int val = va_arg(ap, int);

                if (val > 0) {
                    fmt_ctx.field_width = val;
                }
            } else if (*fmt == '-') {
                ++fmt;
                fmt_ctx.flags |= kFormatFlagAlignLeft;

                while (isdigit(*fmt)) {
                    ++fmt;
                }
            }

            fmt_ctx.precision = 0;
            /* handle precision */
            if (*fmt == '.') {
                ++fmt;
                fmt_ctx.flags &= ~kFormatFlagZeroPad;

                if (isdigit(*fmt)) {
                    fmt_ctx.precision = parse_number(&fmt);
                } else if (*fmt == '*') {
                    ++fmt;
                    int val = va_arg(ap, int);

                    if (val > 0) {
                        fmt_ctx.precision = val;
                    }
                }
            }

            /* handle size specifier */
            switch (*fmt) {
                case 'l': {
                    fmt_ctx.size_specifier = kSizeSpecifier_l;
                    char c = *fmt++;

                    if (*fmt != c) {
                        --fmt;
                    } else {
                        fmt_ctx.size_specifier = kSizeSpecifier_ll;
                    }

                    ++fmt;
                    break;
                }
                case 'h': {
                    char c = *fmt++;
                    fmt_ctx.size_specifier = kSizeSpecifier_h;

                    if (*fmt != c) {
                        --fmt;
                    } else {
                        fmt_ctx.size_specifier = kSizeSpecifier_hh;
                    }

                    ++fmt;
                    break;
                }
                case 'j':fmt_ctx.size_specifier = kSizeSpecifier_j;
                    ++fmt;
                    break;
                case 'z': fmt_ctx.size_specifier = kSizeSpecifier_z;
                    ++fmt;
                    break;
                case 't': fmt_ctx.size_specifier = kSizeSpecifier_t;
                    ++fmt;
                    break;
                case 'L':fmt_ctx.size_specifier = kSizeSpecifier_L;
                    ++fmt;
                    break;
                default:break;
            }

            /* handle conversion specifier */
            switch (*fmt) {
                case 'X':fmt_ctx.radix = 16;
                    {
                        fmt_ctx.flags |= kFormatFlagHugeNumbers;
                        fmt_ctx.flags &= ~kFormatSignedValue;
                        char *ptr = process_number(p_buf, &fmt_ctx, ap, size, &sz);

                        if (ptr != NULL) {
                            p_buf = ptr;
                        }
                    }
                    break;
                case 'x':fmt_ctx.radix = 16;
                    {
                        fmt_ctx.flags &= ~kFormatSignedValue;
                        char *ptr = process_number(p_buf, &fmt_ctx, ap, size, &sz);

                        if (ptr != NULL) {
                            p_buf = ptr;
                        }
                    }
                    break;

                case 'd':
                case 'i':fmt_ctx.radix = 10;
                    {
                        fmt_ctx.flags |= kFormatSignedValue;
                        fmt_ctx.flags &= ~kFormatFlagAlternateForm;
                        char *ptr = process_number(p_buf, &fmt_ctx, ap, size, &sz);

                        if (ptr != NULL) {
                            p_buf = ptr;
                        }
                    }
                    break;

                case 'u':fmt_ctx.radix = 10;
                    {
                        fmt_ctx.flags &= ~kFormatSignedValue;
                        fmt_ctx.flags &= ~kFormatFlagAlternateForm;
                        char *ptr = process_number(p_buf, &fmt_ctx, ap, size, &sz);

                        if (ptr != NULL) {
                            p_buf = ptr;
                        }
                    }
                    break;

                case 'o':fmt_ctx.radix = 8;
                    {
                        fmt_ctx.flags &= ~kFormatSignedValue;
                        char *ptr = process_number(p_buf, &fmt_ctx, ap, size, &sz);

                        if (ptr != NULL) {
                            p_buf = ptr;
                        }
                    }
                    break;

                case 'c': {
                    int c = va_arg(ap, int);

                    if (!(fmt_ctx.flags & kFormatFlagAlignLeft)) {
                        while (fmt_ctx.field_width-- > 1 && sz++ < size) {
                            *p_buf++ = ' ';
                        }
                    }

                    *p_buf++ = c;

                    while (fmt_ctx.field_width-- > 1 && sz++ < size) {
                        *p_buf++ = ' ';
                    }
                }
                    break;

                case 's': {
                    const char *str = va_arg(ap, const char*);
                    str = str == NULL ? "(null)" : str;
                    size_t len = strlen(str);

                    if (!fmt_ctx.precision) {
                        fmt_ctx.precision = len;
                    } else if (len > fmt_ctx.precision) {
                        len = fmt_ctx.precision;
                    }

                    fmt_ctx.field_width -= len;

                    if (!(fmt_ctx.flags & kFormatFlagAlignLeft)) {
                        while (fmt_ctx.field_width-- > 0 && sz++ < size) {
                            *p_buf++ = ' ';
                        }
                    }

                    while (sz++ < size && *str != '\0') {
                        *p_buf++ = *str++;
                    }

                    while (fmt_ctx.field_width-- > 0 && sz++ < size) {
                        *p_buf++ = ' ';
                    }
                }
                    break;

                case 'p': {
                    fmt_ctx.radix = 16;
                    fmt_ctx.field_width = 0;
                    fmt_ctx.precision = 0;
                    fmt_ctx.flags = 0;
                    fmt_ctx.sign = 0;
                    fmt_ctx.flags |= kFormatFlagZeroPad | kFormatFlagAlternateForm | kFormatFlagAlignLeft;
                    fmt_ctx.size_specifier = kSizeSpecifier_ll;

                    size_t addr = va_arg(ap, size_t);

                    if (addr != 0) {
                        char *ptr = format_unsigned(p_buf, addr, &fmt_ctx, size, &sz);

                        if (ptr != NULL) {
                            p_buf = ptr;
                        }
                    } else {
                        const char *nil = "(nil)";

                        while (sz++ < size && *nil != '\0') {
                            *p_buf++ = *nil++;
                        }
                    }
                }
                    break;

                case 'n': {
                    int *p = va_arg(ap, int*);

                    if (p != NULL) {
                        *p = p_buf - buf;
                    }
                }
                    break;

                case '%':*p_buf = '%';
                    break;

                default:
                    if (sz++ < size) {
                        *p_buf++ = *fmt;
                    }
                    break;
            }
        }

        *p_buf = '\0';
        return p_buf - buf;
    }

    return 0;
}

int snprintf(char *buffer, size_t size, const char *fmt, ...) {
    int res = -1;
    va_list ap;
    va_start(ap, fmt);
    res = vsnprintf(buffer, size, fmt, ap);
    va_end(ap);
    return res;
}