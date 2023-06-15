#include <ctype.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>

__USING_MACONDO_TEST_NAMESPACE

#define MAX_NUMBER_LEN 66
#define SPRINTF_MAX_BUFFER_SIZE 1024

struct PrintfSizeSpecifier {
    enum {
        kChar = 1,
        kShort = 1 << 1,
        kLong = 1 << 2,
        kLongLong = 1 << 3,
        kIntUintMax = 1 << 4,
        kSizeT = 1 << 5,
        kPtrDiffT = 1 << 6
    };
};

struct PrintfConversionSpecifier {
    enum {
        kInt = 1,
        kUnsigned = 1 << 1,
        kChar = 1 << 2,
        kString = 1 << 3,
        kPointer = 1 << 4,
        kNLen = 1 << 5,
        kPercent = 1 << 6
    };
};

struct PrintfFormatFlag {
    enum {
        kMinus = 1,
        kPlus = 1 << 1,
        kSpace = 1 << 2,
        kSpecial = 1 << 3,
        kZero = 1 << 4,
        kHugeNumbers = 1 << 5
    };
};

struct PrintfFormatArg {
    enum {
        kUnknown = 0,
        kSignedValue = 1,
        kPointer = 1 << 1,
        kNegativeValue = 1 << 2,
        kPrecisionOmitted = 1 << 3
    };
};

struct Flags {
    int flags = 0;
    Flags() = default;
    Flags(int value) : flags(value) {}
    bool checkFlag(int value) const {
        return flags & value;
    }
    void setFlag(int value) {
        flags |= value;
    }
    void clearFlag(int value) {
        flags &= ~value;
    }
    void reset() {
        flags = 0;
    }
};


struct FormatSpec {
    Flags printfSizeSpecifier;
    Flags printfConversionSpecifier;
    Flags printfFormatFlags;
    Flags flags = 0;
    int precision = 0;
    int field_width = 0;
    int radix = 10;

    void reset() {
        printfSizeSpecifier.reset();
        printfConversionSpecifier.reset();
        printfFormatFlags.reset();
        flags.reset();
        precision = -1;
        field_width = -1;
        radix = 10;
    }
};

/* Parses number and moves pointer to first non digit character */
static int parse_number(const char **str) {
    int result = 0;

    while (isdigit(**str)) {
        result = result * 10 + *((*str)++) - '0';
    }

    return result;
}

/**
 * @brief format_number - implementing format number and output string has length not more than max_size
 * @param buffer        - destination buffer
 * @param arg           - the number to format
 * @param formatSpec    - format spec with printf flags etc
 * @param max_size      - maximum allowed length
 * @return length of formatted number
 */
static size_t format_number(char *buffer, unsigned long long arg, FormatSpec& formatSpec, size_t max_size)
{
    size_t len = 0;
    unsigned long long number = arg;
    int number_len = 0;
    int sign = -1;
    char num_str[MAX_NUMBER_LEN];
    const char *digits = formatSpec.printfFormatFlags.checkFlag(PrintfFormatFlag::kHugeNumbers)
                         ? "0123456789ABCDEF"
                         : "0123456789abcdef";

    /* Catch sign for signed numbers */
    if (formatSpec.flags.checkFlag(PrintfFormatArg::kSignedValue)) {
        if (formatSpec.flags.checkFlag(PrintfFormatArg::kNegativeValue)) {
            sign = '-';
        } else if (formatSpec.printfFormatFlags.checkFlag(PrintfFormatFlag::kPlus)) {
            sign = '+';
        } else if (formatSpec.printfFormatFlags.checkFlag(PrintfFormatFlag::kSpace)) {
            sign = ' ';
        }

        if (sign > 0) {
            -- formatSpec.field_width;
        }
    }

    /* Generate number array in reverse order */
    if (number != 0) {
        while (number != 0) {
            unsigned long long n = number % formatSpec.radix;
            number /= formatSpec.radix;
            num_str[number_len++] = digits[n];
        }
    } else {
        num_str[number_len++] = formatSpec.flags.checkFlag(PrintfFormatArg::kPrecisionOmitted) ? ' ' : '0';

        /* do not paint 0x0 or 00 ??? */
        if (formatSpec.printfFormatFlags.checkFlag(PrintfFormatFlag::kSpecial)) {
            if (len < max_size) {
                *buffer ++ = '0';
                ++ len;
            }

            return len;
        }
    }

    if (formatSpec.precision < number_len) {
        formatSpec.precision = number_len;
    }

    /* precision has priority over field width */
    formatSpec.field_width -= formatSpec.precision;
    formatSpec.precision -= number_len;

    /* decrease field width. we need take an account special form */
    if (formatSpec.printfFormatFlags.checkFlag(PrintfFormatFlag::kSpecial)) {
        if (formatSpec.radix != 10) {
            -- formatSpec.field_width;
            if (formatSpec.radix == 16) {
                -- formatSpec.field_width;
            }
        }
    }

    /* No align left and zero padding */
    if (!formatSpec.printfFormatFlags.checkFlag(PrintfFormatFlag::kMinus)) {
        if (!formatSpec.printfFormatFlags.checkFlag(PrintfFormatFlag::kZero)) {
            /* leading padding */
            while (-- formatSpec.field_width >= 0 && len < max_size) {
                *buffer++ = ' ';
                ++ len;
            }
        }
    }
    /* write sign or space depends from format flags */
    if (sign > 0 && len < max_size) {
        *buffer ++ = sign;
        ++len;
    }

    /* handle alternate form prefix here */
    if (formatSpec.printfFormatFlags.checkFlag(PrintfFormatFlag::kSpecial)) {
        if (formatSpec.radix != 10) {
            if (len < max_size) {
                *buffer ++ = '0';
                ++ len;
            }
            if (formatSpec.radix == 16) {
                if (len < max_size) {
                    *buffer ++ = formatSpec.printfFormatFlags.checkFlag(PrintfFormatFlag::kHugeNumbers) ? 'X' : 'x';
                    ++ len;
                }
            }
        }
    }

    /* prepend zeros if min precision requires it */
    while (-- formatSpec.precision >= 0 && len < max_size) {
        *buffer++ = '0';
        ++ len;
    }

    /* padding after sign ??? what if no zero ??? */
    if (!formatSpec.printfFormatFlags.checkFlag(PrintfFormatFlag::kMinus)) {
        char pad = formatSpec.printfFormatFlags.checkFlag(PrintfFormatFlag::kZero) ? '0' : ' ';

        while (-- formatSpec.field_width >= 0 && len < max_size) {
            *buffer++ = pad;
            ++ len;
        }
    }

    while (-- formatSpec.precision >= 0 && len < max_size) {
        *buffer++ = '0';
        ++ len;
    }
    /* write number itself */
    for (int i = number_len - 1; i >= 0 && len < max_size;  --i, -- formatSpec.precision, ++len) {
        *buffer++ = num_str[i];
    }

    /* trailing padding */
    while (-- formatSpec.field_width >= 0 && len < max_size) {
        *buffer++ = ' ';
        ++ len;
    }

    *buffer = '\0';
    return len;
}

static size_t format_char(char *buffer, int arg, FormatSpec& formatSpec, size_t max_size) {
    size_t len = 1;

    if (!formatSpec.printfFormatFlags.checkFlag(PrintfFormatFlag::kMinus)) {
        for (; (formatSpec.field_width > 1) && (len < max_size); formatSpec.field_width--, len ++) {
            *buffer++ = ' ';
        }
    }

    *buffer++ = arg;

    for (; (formatSpec.field_width > 1) && (len < max_size); formatSpec.field_width--, len ++) {
        *buffer++ = ' ';
    }

    return len;
}

static long long read_signed_number(const FormatSpec& formatSpec, va_list ap) {
    long long value = 0;

    switch (formatSpec.printfSizeSpecifier.flags) {
        case PrintfSizeSpecifier::kChar:
            value = static_cast<signed char> (va_arg(ap, int));
            break;

        case PrintfSizeSpecifier::kIntUintMax:
            value = va_arg(ap, intmax_t);
            break;

        case PrintfSizeSpecifier::kLong:
            value = va_arg(ap, long);
            break;

        case PrintfSizeSpecifier::kLongLong:
            value = va_arg(ap, long long);
            break;

        case PrintfSizeSpecifier::kPtrDiffT:
            value = va_arg(ap, ptrdiff_t);
            break;

        case PrintfSizeSpecifier::kShort:
            value = static_cast<signed short> (va_arg(ap, int));
            break;

        case PrintfSizeSpecifier::kSizeT:
            value = static_cast<ssize_t> (va_arg(ap, int));
            break;
        default:
            value = va_arg(ap, int);
    }

    return value;
}

static unsigned long long read_unsigned_number(const FormatSpec& formatSpec, va_list ap) {
    unsigned long long value = 0;

    switch (formatSpec.printfSizeSpecifier.flags) {

        case PrintfSizeSpecifier::kChar:
            value = static_cast<signed char> (va_arg(ap, unsigned int));
            break;

        case PrintfSizeSpecifier::kIntUintMax:
            value = va_arg(ap, uintmax_t);
            break;

        case PrintfSizeSpecifier::kLong:
            value = va_arg(ap, unsigned long);
            break;

        case PrintfSizeSpecifier::kLongLong:
            value = va_arg(ap, unsigned long long);
            break;

        case PrintfSizeSpecifier::kPtrDiffT:
            value = va_arg(ap, ptrdiff_t);
            break;

        case PrintfSizeSpecifier::kShort:
            value = static_cast<unsigned short> (va_arg(ap, unsigned int));
            break;

        case PrintfSizeSpecifier::kSizeT:
            value = static_cast<size_t> (va_arg(ap, unsigned int));
            break;
        default:
            value = va_arg(ap, unsigned int);
    }

    return value;
}

static size_t format_string(char *buffer, const char* str, FormatSpec& formatSpec, size_t max_size) {
    size_t len = 0;

    if (str) {
        int str_len = strlen(str);

        if (formatSpec.flags.checkFlag(PrintfFormatArg::kPrecisionOmitted)) {
            if (formatSpec.field_width <= 0) {
                return 0;
            }
        } else if (formatSpec.precision <= 0 || formatSpec.precision > str_len) {
            formatSpec.precision = str_len;
        }

        if (formatSpec.field_width > formatSpec.precision && formatSpec.precision > 0) {
            formatSpec.field_width -= formatSpec.precision;
        }

        if (!formatSpec.printfFormatFlags.checkFlag(PrintfFormatFlag::kMinus)) {
            for (; formatSpec.field_width > 0 && len < max_size; formatSpec.field_width--, len ++) {
                *buffer++ = ' ';
            }
        }

        for (; formatSpec.precision -- > 0 && len < max_size; len ++) {
            *buffer++ = *str++;
        }

        for (; formatSpec.field_width > 0 && len < max_size; formatSpec.field_width--, len ++) {
            *buffer++ = ' ';
        }
    } else {
        /* just print (null) */
        if (len < max_size) {
            *buffer ++ = '(';
            len ++;
        }

        if (len < max_size) {
            *buffer ++ = 'n';
            len++;
        }

        if (len < max_size) {
            *buffer ++ = 'u';
            len++;
        }

        if (len < max_size) {
            *buffer ++ = 'l';
            len++;
        }

        if (len < max_size) {
            *buffer ++ = 'l';
            len++;
        }

        if (len < max_size) {
            *buffer ++ = ')';
            len++;
        }
    }

    return len;
}

static size_t format_pointer(char *buffer, unsigned long long addr, FormatSpec& formatSpec, size_t max_size) {
    size_t len = 0;

    formatSpec.reset();
    formatSpec.printfFormatFlags.setFlag(PrintfFormatFlag::kSpecial);
    formatSpec.printfFormatFlags.setFlag(PrintfFormatFlag::kZero);
    formatSpec.printfFormatFlags.setFlag(PrintfFormatFlag::kMinus);

    if (addr != 0) {
        len = format_number(buffer, addr, formatSpec, max_size);
    } else {
        if (len < max_size) {
            *buffer ++ = '(';
            len ++;
        }

        if (len < max_size) {
            *buffer ++ = 'n';
            len++;
        }

        if (len < max_size) {
            *buffer ++ = 'i';
            len++;
        }

        if (len < max_size) {
            *buffer ++ = 'l';
            len++;
        }

        if (len < max_size) {
            *buffer ++ = ')';
            len++;
        }
    }

    return len;
}

__BEGIN_DECLS

/**
 * @brief vsnprintf -
 * @param buf          -
 * @param size         -
 * @param fmt          -
 * @param ap           -
 * @return number of written characters (len of formatted output string)
 *
 * Zero precision means it gonna print nothing. Omitted precision after a dot means precision is zero.
 */
int vsnprintf(char *buf, size_t size, const char *fmt, va_list ap) {
    if (size > 1 && buf && fmt) {
        char *p_buf = buf;
        FormatSpec formatSpec;
        bool isNegative = false;
        --size;

        if (size == 0) {
            return size;
        }

        for (size_t sz = 0; (sz < size) && (*fmt != '\0'); ++sz, ++fmt) {
            if (*fmt != '%') {
                *p_buf++ = *fmt;
                continue;
            }

            formatSpec.reset();

            /* handle format flags */
            while (*fmt++ != '\0') {
                switch (*fmt) {
                    case '#':
                        formatSpec.printfFormatFlags.setFlag(PrintfFormatFlag::kSpecial);
                        formatSpec.printfFormatFlags.clearFlag(PrintfFormatFlag::kPlus);
                        continue;

                    case ' ':
                        formatSpec.printfFormatFlags.setFlag(PrintfFormatFlag::kSpace);
                        formatSpec.printfFormatFlags.clearFlag(PrintfFormatFlag::kZero);
                        continue;

                    case '0':
                        formatSpec.printfFormatFlags.setFlag(PrintfFormatFlag::kZero);
                        continue;

                    case '-':
                        formatSpec.printfFormatFlags.setFlag(PrintfFormatFlag::kMinus);
                        formatSpec.printfFormatFlags.clearFlag(PrintfFormatFlag::kZero);
                        continue;

                    case '+':
                        formatSpec.printfFormatFlags.setFlag(PrintfFormatFlag::kPlus);
                        formatSpec.printfFormatFlags.clearFlag(PrintfFormatFlag::kSpace);
                        continue;

                    default:
                        break;
                }

                break;
            }

            /* handle field width */
            isNegative = false;

            if (*fmt == '-') {
                ++fmt;
                isNegative = true;
            } else if (isdigit(*fmt)) {
                formatSpec.field_width = parse_number(&fmt);
            } else if (*fmt == '*') {
                ++fmt;
                formatSpec.field_width = va_arg(ap, int);

                if (formatSpec.field_width < 0) {
                    formatSpec.field_width = -formatSpec.field_width;
                    isNegative = true;
                }
            }

            if (isNegative) {
                formatSpec.printfFormatFlags.setFlag(PrintfFormatFlag::kMinus);
            }

            /* handle precision */
            if (*fmt == '.') {
                ++fmt;
                formatSpec.printfFormatFlags.clearFlag(PrintfFormatFlag::kZero);
                formatSpec.printfFormatFlags.clearFlag(PrintfFormatFlag::kSpace);

                if (isdigit(*fmt)) {
                    formatSpec.precision = parse_number(&fmt);
                    /* catch explicit set of precision to 0 via "%.0" */
                    if (formatSpec.precision == 0) {
                        formatSpec.flags.setFlag(PrintfFormatArg::kPrecisionOmitted);
                    }
                } else if (*fmt == '*') {
                    ++fmt;
                    formatSpec.precision = va_arg(ap, int);
                } else if (*fmt == '-') { /* Should I catch '+' here ??? */
                    /* Negative precision should be set as zero */
                    formatSpec.precision = 0;
                    /* just skip digits */
                    parse_number(&++fmt);
                }
                else {
                    formatSpec.flags.setFlag(PrintfFormatArg::kPrecisionOmitted);
                }
            }

            /* handle size specifier */
            switch (*fmt) {
                case 'l': {
                    char c = *fmt++;

                    if (*fmt != c) {
                        formatSpec.printfSizeSpecifier.setFlag(PrintfSizeSpecifier::kLong);
                        --fmt;
                    } else {
                        formatSpec.printfSizeSpecifier.setFlag(PrintfSizeSpecifier::kLongLong);
                    }

                    ++fmt;
                    break;
                }
                case 'h': {
                    char c = *fmt++;

                    if (*fmt != c) {
                        formatSpec.printfSizeSpecifier.setFlag(PrintfSizeSpecifier::kShort);
                        --fmt;
                    } else {
                        formatSpec.printfSizeSpecifier.setFlag(PrintfSizeSpecifier::kChar);
                    }

                    ++fmt;
                    break;
                }
                case 'j':
                    formatSpec.printfSizeSpecifier.setFlag(PrintfSizeSpecifier::kIntUintMax);
                    ++fmt;
                    break;
                case 't':
                    formatSpec.printfSizeSpecifier.setFlag(PrintfSizeSpecifier::kPtrDiffT);
                    ++fmt;
                    break;
                case 'L':
                    formatSpec.printfSizeSpecifier.setFlag(PrintfSizeSpecifier::kLongLong);
                    ++fmt;
                    break;
                case 'z':
                    formatSpec.printfSizeSpecifier.setFlag(PrintfSizeSpecifier::kSizeT);
                    ++fmt;
                    break;
                default:
                    break;
            }

            /* handle conversion specifier */
            switch (*fmt) {
                case 'X' :
                    formatSpec.printfFormatFlags.setFlag(PrintfFormatFlag::kHugeNumbers);
                    [[fallthrough]];
                case 'x': {
                    formatSpec.radix = 16;
                    unsigned long long value = read_unsigned_number(formatSpec, ap);
                    size_t len = format_number(p_buf, value, formatSpec, size - sz);
                    sz += len;
                    p_buf += len;
                }
                    break;

                case 'p':
                {
                    formatSpec.radix = 16;
                    formatSpec.printfSizeSpecifier.checkFlag(PrintfSizeSpecifier::kSizeT);
                    unsigned long long value = read_unsigned_number(formatSpec, ap);
                    size_t len = format_pointer(p_buf, value, formatSpec, size - sz);
                    sz += len;
                    p_buf += len;
                }
                    break;

                case 'd':
                    [[fallthrough]];
                case 'i': {
                    formatSpec.radix = 10;
                    long long value = read_signed_number(formatSpec, ap);

                    formatSpec.flags.setFlag(PrintfFormatArg::kSignedValue);

                    if (value < 0) {
                        formatSpec.flags.setFlag(PrintfFormatArg::kNegativeValue);
                        value = -value;
                    }

                    size_t len = format_number(p_buf, value, formatSpec, size - sz);
                    sz += len;
                    p_buf += len;
                }
                    break;

                case 'o':
                    formatSpec.radix = 8;
                    [[fallthrough]];
                case 'u': {
                    unsigned long long value = read_unsigned_number(formatSpec, ap);
                    size_t len = format_number(p_buf, value, formatSpec, size - sz);
                    sz += len;
                    p_buf += len;
                }
                    break;

                case 's': {
                    const char *str = va_arg(ap, const char*);
                    size_t len = format_string(p_buf, str, formatSpec, size - sz);
                    /// TODO: think about it. len like flags resets each iteration??? and check it at end
                    sz += len;
                    p_buf += len;
                }
                    break;

                case 'c': {
                    int c = va_arg(ap, int);
                    size_t len = format_char(p_buf, c, formatSpec, size - sz);
                    sz += len;
                    p_buf += len;
                }
                    break;

                case '%':
                    *p_buf ++ = '%';
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
    } else if (buf) {
        *buf = '\0';
        return 0;
    }

    return -1;
}

int snprintf(char *buffer, size_t size, const char *fmt, ...) {
    int res = -1;
    va_list ap;
    va_start(ap, fmt);
    res = vsnprintf(buffer, size, fmt, ap);
    va_end(ap);
    return res;
}

int sprintf(char *buffer, const char *fmt, ...)
{
    int res = -1;
    va_list ap;
    va_start(ap, fmt);
    res = vsnprintf(buffer, SPRINTF_MAX_BUFFER_SIZE, fmt, ap);
    va_end(ap);
    return res;
}

__END_DECLS