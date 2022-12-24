#ifndef SRC_S21_SPRINTF_H_
#define SRC_S21_SPRINTF_H_
#include "s21_string.h"
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <locale.h>
#include <stdint.h>
#include <stdbool.h>
#define SIZE 512

typedef struct {
    bool plus;
    bool minus;
    bool space;
    bool hash;
    int precision;
    int isPrecision;
    int width;
    char length;
    char specifier;
} flags;

const char *check_flags(const char *format, flags *flag);
const char *check_width(const char *format, flags *flag, va_list input);
const char *check_precision(const char *format, flags *flag, va_list input);
const char *check_length(const char *format, flags *flag);
int is_num(char ch);
int char_to_int(const char *str);
void conversion(flags flag, char *buffer, va_list input);
void pars_int(flags flag, char *buffer, va_list input);
void pars_char(flags flag, char *buffer, va_list input);
void pars_str(flags flag, char *buffer, va_list input);
void pars_float(flags flag, char *buffer, va_list input);
void pars_unsigned(flags flag, char *buffer, va_list input);
void num_to_string(int64_t value, char *buffer);
void precision(char *buffer, flags flag);
void use_flags(char *buffer, flags flag);
void w_to_str(flags flag, char *buffer, const wchar_t *wc);
void char_to_str(flags flag, char *buffer, char c);
void str_to_str(flags flag, char *buffer, char *str);
void float_to_str(double value, char *str, flags flag);
void reverse(char *s);

#endif  //  SRC_S21_SPRINTF_H_
