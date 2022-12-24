#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    bool e;
    bool i;
    bool v;
    bool c;
    bool l;
    bool n;
    int error;
    char* filename;
    int REG_FLAG;
    bool string_without_e_recorded;
    int c_counter;
    int n_counter;
    bool l_printed;
    bool c_print_another;
    char error_flag;
    int number_of_files;
    size_t number_of_search_strings;
    bool n_print_extented;
    bool e_recorded;
    size_t e_counter;
    bool e_is_true;
    bool void_pattern;
} flags;

void checkPattern(flags* flag, int argc, char** argv);
void showError(flags* flag);
void taskPrint(flags* flag, FILE* stream, char* search_strings,
               char* search_string);
int s21_getline(FILE* stream, char* temp_string);
void init_flags(flags* flag);

#endif  // SRC_GREP_S21_GREP_H_
