#ifndef SRC_S21_STRINGPLUS_H_
#define SRC_S21_STRINGPLUS_H_
#include "s21_string.h"
#include "s21_sprintf.h"
#include <stdio.h>
#include <string.h>
#include <check.h>
#include <limits.h>
#define SMAX 512

char test1[20] = "Hello world\0";
char test2[20] = "Hello world\n\0";
char test3[20] = "a\n\0";
char test4[15] = " \n\0";
char test5[15] = " \0";
char test6[15] = "\n\0";
char test7[15] = "\0";

#endif  // SRC_S21_STRINGPLUS_H_
