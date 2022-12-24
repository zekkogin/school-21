#include "s21_sprintf.h"

int s21_sprintf(char *str, const char *format, ...) {
    flags flag = {0};
    va_list input;
    va_start(input, format);
    char *zero = str;
    while (*format) {
        char buffer[SIZE] = {'\0'};
        if (*format != '%') {
            *str++ = *format++;
            continue;
        } else {
            format++;
            s21_memset(&flag, 0, sizeof(flags));
        }
        format = check_flags(format, &flag);
        format = check_width(format, &flag, input);
        format = check_precision(format, &flag, input);
        format = check_length(format, &flag);
        flag.specifier = *format;
        format++;
        conversion(flag, buffer, input);
        for (int i = 0; buffer[i]; i++, str++) {
            *str = buffer[i];
        }
    }
    *str = '\0';
    va_end(input);
    return str - zero;
}

const char *check_flags(const char *format, flags *flag) {
    while (*format == '+' || *format == '-' || *format == ' ') {
        if (*format == '+') {
            flag->plus = true;
        } else if (*format == '-') {
            flag->minus = true;
        } else if (*format == ' ') {
            flag->space = true;
        }
        format++;
    }
    return format;
}

const char *check_width(const char *format, flags *flag, va_list input) {
    if (is_num(*format)) {
        char temp[SIZE] = {'\0'};
        for (int i = 0; is_num(*format); i++, format++) {
            temp[i] = *format;
        }
        flag->width = char_to_int(temp);
    }
    return format;
}

const char *check_precision(const char *format, flags *flag, va_list input) {
    if (*format == '.') {
        flag->isPrecision = true;
        format++;
    }
    if (is_num(*format)) {
        char temp[SIZE] = {'\0'};
        for (int i = 0; is_num(*format); i++, format++) {
            temp[i] = *format;
        }
        flag->precision = char_to_int(temp);
    }
    return format;
}

const char *check_length(const char *format, flags *flag) {
    if (*format == 'h') {
        flag->length = 'h';
        format++;
    } else if (*format == 'l') {
        flag->length = 'l';
        format++;
    }
    return format;
}

int is_num(char ch) { return ('0' <= ch && ch <= '9'); }

int char_to_int(const char *str) {
    int res = 0;
    while (*str && is_num(*str)) {
        res = res * 10 + (*str - '0');
        str++;
    }
    return res;
}

void conversion(flags flag, char *buffer, va_list input) {
    if (flag.specifier == 'd' || flag.specifier == 'i') {
        pars_int(flag, buffer, input);
    } else if (flag.specifier == 'c') {
        pars_char(flag, buffer, input);
    } else if (flag.specifier == 's') {
        pars_str(flag, buffer, input);
    } else if (flag.specifier == 'f') {
        pars_float(flag, buffer, input);
    } else if (flag.specifier == 'u') {
        pars_unsigned(flag, buffer, input);
    } else if (flag.specifier == '%') {
        buffer[0] = '%';
    }
}

void wchar_to_str(flags flag, char *buffer, wchar_t wc) {
    if (!flag.minus && flag.width) {
        char temp[SIZE] = {'\0'};
        wcstombs(temp, &wc, SIZE);
        for (s21_size_t i = 0; i < flag.width - s21_strlen(temp); i++) {
            buffer[i] = ' ';
        }
        s21_strcat(buffer, temp);
    } else if (flag.width) {
        wcstombs(buffer, &wc, SIZE);
        for (int i = s21_strlen(buffer); i < flag.width; i++) {
            buffer[i] = ' ';
        }
    } else {
        wcstombs(buffer, &wc, SIZE);
    }
}

void pars_int(flags flag, char *buffer, va_list input) {
    int64_t value = va_arg(input, int64_t);
    if (flag.precision == 0 && value == 0 && flag.plus) {
        buffer[0] = '+';
        // } else if (flag.precision == 0 && value == 0) {
        //     buffer[0] = '\0';
    } else {
        if (flag.length == 0) {
            value = (int32_t)value;
        } else if (flag.length == 'h') {
            value = (int16_t)value;
        }
        num_to_string(value, buffer);
        precision(buffer, flag);
        use_flags(buffer, flag);
    }
}

void pars_char(flags flag, char *buffer, va_list input) {
    if (flag.length == 'l') {
        wchar_t wc;
        wc = va_arg(input, wchar_t);
        wchar_to_str(flag, buffer, wc);
    } else {
        char c;
        c = va_arg(input, int);
        char_to_str(flag, buffer, c);
    }
}

void pars_str(flags flag, char *buffer, va_list input) {
    if (flag.length == 'l') {
        wchar_t *wc = va_arg(input, wchar_t *);
        w_to_str(flag, buffer, wc);
    } else {
        char *c = va_arg(input, char *);
        if (c == s21_NULL) {
            c = "(null)";
        }
        str_to_str(flag, buffer, c);
    }
}

void pars_float(flags flag, char *buffer, va_list input) {
    double value = 0;
    if (flag.length == 'l') {
        value = va_arg(input, double);
    } else {
        value = va_arg(input, double);
    }
    if (!flag.isPrecision) {
        flag.precision = 6;
    }
    float_to_str(value, buffer, flag);
    use_flags(buffer, flag);
}

void pars_unsigned(flags flag, char *buffer, va_list input) {
    uint64_t value = va_arg(input, uint64_t);
    switch (flag.length) {
        case 'h':
            value = (uint16_t)value;
            break;
        case 'l':
            value = (uint64_t)value;
            break;
        case 0:
            value = (uint32_t)value;
    }
    num_to_string(value, buffer);
    precision(buffer, flag);
    use_flags(buffer, flag);
}

void num_to_string(int64_t value, char *buffer) {
    int sign = 1;
    if (value == LONG_MIN) {
        s21_strcpy(buffer, "-9223372036854775808");
    } else if (value == ULONG_MAX) {
        s21_strcpy(buffer, "18446744073709551615");
    } else {
        if (value < 0) {
            sign = 0;
            value = -value;
        }
        int i = 0;
        do {
            buffer[i] = value % 10 + '0';
            value = value / 10;
            i++;
        } while (value > 0);
        if (sign == 0) {
            buffer[i++] = '-';
        }
        buffer[i] = '\0';
        reverse(buffer);
    }
}

void precision(char *buffer, flags flag) {
    char temp[SIZE] = {'\0'};
    int sign = 0;
    int len = s21_strlen(buffer);
    if (buffer[0] == '-') {
        temp[0] = '-';
        len--;
        sign = 1;
    }
    if (flag.precision > len) {
        int index;
        for (index = sign; index < flag.precision - len + sign; index++) {
            temp[index] = '0';
        }
        for (int i = sign; buffer[i]; i++, index++) {
            temp[index] = buffer[i];
        }
        s21_strcpy(buffer, temp);
    }
}

void use_flags(char *buffer, flags flag) {
    char temp[SIZE + 1] = {'\0'};
    if (flag.plus && flag.specifier != 'u') {
        temp[0] = buffer[0] == '-' ? buffer[0] : '+';
        s21_strcpy(temp + 1, buffer[0] == '-' ? buffer + 1 : buffer);
        s21_strcpy(buffer, temp);
    } else if (flag.space && buffer[0] != '-' && flag.specifier != 'u') {
        temp[0] = ' ';
        s21_strcpy(temp + 1, buffer);
        s21_strcpy(buffer, temp);
    }
    if (flag.width > (int)s21_strlen(buffer)) {
        int index = flag.width - s21_strlen(buffer);
        if (!flag.minus) {
            s21_memset(temp, ' ', index);
            s21_strcpy(temp + index, buffer);
        } else {
            s21_strcpy(temp, buffer);
            s21_memset(temp + s21_strlen(temp), ' ', index);
        }
        s21_strcpy(buffer, temp);
    }
}

void char_to_str(flags flag, char *buffer, char c) {
    if (!flag.minus && flag.width) {
        for (int i = 0; i < flag.width; i++) {
            buffer[i] = ' ';
            if (i == flag.width - 1) {
                buffer[i] = c;
            }
        }
    } else if (flag.width) {
        buffer[0] = c;
        for (int i = 1; i < flag.width; i++) {
            buffer[i] = ' ';
        }
    } else {
        buffer[0] = c;
    }
}

void str_to_str(flags flag, char *buffer, char *str) {
    char temp[SIZE] = {'\0'};
    s21_strcpy(temp, str);
    if (flag.isPrecision) temp[flag.precision] = '\0';

    int w = flag.width - s21_strlen(temp);
    int len = s21_strlen(temp);

    if (flag.minus && w > 0) {
        s21_strcpy(buffer, temp);
        s21_memset(buffer + len, ' ', w);
    } else if (w > 0) {
        s21_memset(buffer, ' ', w);
        s21_strcpy(buffer + w, temp);
    } else {
        s21_strcpy(buffer, temp);
    }
}

void w_to_str(flags flag, char *buffer, const wchar_t *wc) {
    char temp[SIZE] = {'\0'};
    char str[SIZE] = {'\0'};
    int w = flag.width - s21_strlen(temp);
    wcstombs(str, wc, SIZE);
    s21_strcpy(temp, str);
    if (flag.isPrecision) temp[flag.precision] = '\0';
    if (flag.minus && w > 0) {
        s21_strcpy(buffer, temp);
        s21_memset(buffer + s21_strlen(temp), ' ', w);
    } else if (w > 0) {
        s21_memset(buffer, ' ', w);
        s21_strcpy(buffer + w, temp);
    } else {
        s21_strcpy(buffer, temp);
    }
}

void float_to_str(double value, char *str, flags flag) {
    char buffer[SIZE] = {'\0'};
    int index = SIZE - 2;
    bool sign = 0;
    if (value < 0) {
        sign = 1;
        value = -value;
    } else {
        sign = 0;
    }
    double l = 0;
    double r = modf(value, &l);
    if (flag.precision == 0) {
        l = roundl(value);
        r = 0;
    }
    char f[SIZE] = {'\0'};
    for (int i = 0; i < flag.precision; i++) {
        r = r * 10;
        f[i] = (int)r + '0';
    }
    long long rt = roundl(r), left = l;
    if (!rt) {
        for (int i = 0; i < flag.precision; index--, i++) buffer[index] = '0';
    } else {
        for (int i = s21_strlen(f); rt || i > 0; rt /= 10, index--, i--)
            buffer[index] = (int)(rt % 10 + 0.05) + '0';
    }
    if ((flag.isPrecision && flag.precision != 0) || (int)r ||
        (!flag.isPrecision && value == 0) || s21_strlen(f))
        buffer[index--] = '.';
    if (!left) {
        buffer[index] = '0';
        index--;
    } else {
        for (; left; left /= 10, index--)
            buffer[index] = (int)(left % 10) + '0';
    }
    for (int i = 0; buffer[index + 1]; index++, i++) {
        if (sign == 1) {
            str[0] = '-';
            i++;
            sign = 0;
        }
        str[i] = buffer[index + 1];
    }
}

void reverse(char *s) {
    int i = 0;
    int j = s21_strlen(s) - 1;
    for (; i < j; i++, j--) {
        char c;
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
