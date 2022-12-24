#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    bool stop;
    bool b;
    bool e;
    bool n;
    bool s;
    bool t;
    bool v;
    bool T;
    bool E;
    int error;  // 1 - file doesn't exist,  2 - illegal option
    char *filename;
    int number_of_string;
    int number_of_non_void_string;
    char wrongflag;
} flags;

void taskPrint(FILE *stream, flags *flag);
void showError(flags *flag);

#endif  // SRC_CAT_S21_CAT_H_
