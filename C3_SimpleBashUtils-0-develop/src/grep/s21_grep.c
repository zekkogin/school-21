#include "s21_grep.h"

/* Parse flags and remember filenames */

int main(int argc, char **argv) {
    flags flag;
    init_flags(&flag);
    if (argc > 2) {
        checkPattern(&flag, argc, argv);
        int err_break = 0;
        // for pattern with -e (zapis cherez A|B)
        char search_strings[1024] = {'\0'};
        char search_string[1024] = {'\0'};  // for pattern without -e
        char *filenames[1024] = {'\0'};
        int counter = 1;
        for (; counter < argc; counter++) {
            if (argv[counter][0] == '-' && err_break != 1 && flag.e == false) {
                int length = strlen(argv[counter]);
                /* Proverka na REDFLAG */
                err_break = strspn(argv[counter], "-eivcln");
                if (err_break != length) {
                    flag.error_flag = argv[counter][err_break];
                    flag.error = 2;
                    showError(&flag);
                    break;
                }
                for (int i = 1; i < length; i++) {
                    if (argv[counter][i] == 'e') {
                        flag.e = true;
                        flag.e_counter++;
                    }
                    if (argv[counter][i] == 'i') {
                        flag.i = true;
                    }
                    if (argv[counter][i] == 'v') {
                        flag.v = true;
                    }
                    if (argv[counter][i] == 'c') {
                        flag.c = true;
                    }
                    if (argv[counter][i] == 'l') {
                        flag.l = true;
                    }
                    if (argv[counter][i] == 'n') {
                        flag.n = true;
                    }
                }
                continue;
            }
            //     flag.void_pattern = true;  // proverka na ""
            if (flag.e == false && argv[counter][0] != '-' &&
                flag.string_without_e_recorded == false &&
                flag.e_is_true == false) {
                strcpy(search_string, argv[counter]);
                flag.number_of_search_strings++;
                flag.string_without_e_recorded = true;
                continue;
            }
            if (flag.e == true) {
                strcat(search_strings, argv[counter]);
                strcat(search_strings, "|");
                flag.number_of_search_strings++;
                flag.e_recorded = true;
                flag.e = false;
                continue;
            }
            if (argv[counter][0] != '-' && flag.e == false) {
                filenames[flag.number_of_files] = argv[counter];
                flag.number_of_files++;
                if (flag.number_of_files >= 2) {
                    flag.c_print_another = true;
                    flag.n_print_extented = true;
                }
            }
        }
        // Proverka na kol-vo shablonov i -e
        if ((flag.string_without_e_recorded == true &&
             flag.e_counter != flag.number_of_search_strings - 1) ||
            (flag.string_without_e_recorded == false &&
             flag.e_counter != flag.number_of_search_strings)) {
            flag.error = 3;
        }
        for (int i = 0; i < flag.number_of_files; i++) {
            if (flag.error == 3) {
                showError(&flag);
                break;
            }
            FILE *stream;
            stream = fopen(filenames[i], "r");
            if (stream == NULL) {
                flag.error = 1;
                flag.filename = filenames[i];
            }
            if (flag.error == 0) {
                flag.filename = filenames[i];
                taskPrint(&flag, stream, search_strings, search_string);
                fclose(stream);
                flag.n_counter = 1;
                flag.l_printed = false;
            }
            if (flag.error != 0) {
                showError(&flag);
                if (flag.error != 0) break;
            }
        }
    }
}

void checkPattern(flags *flag, int argc, char **argv) {
    int counter = 1;
    for (; counter < argc; counter++) {
        if (argv[counter][0] == '-') {
            int length = strlen(argv[counter]);
            for (int i = 1; i < length; i++) {
                if (argv[counter][i] == 'e') {
                    flag->e_is_true = true;
                }
            }
        }
    }
}

/* Main function after parse flags */

void taskPrint(flags *flag, FILE *stream, char *search_strings,
               char *search_string) {
    char temp_string[1024] = {};
    char temp_string_for_n[1024] = {};
    char temp_string_for_extented_filename[1024] = {};
    int length_of_regex_string = strlen(search_strings);
    search_strings[length_of_regex_string - 1] = '\0';
    regex_t regex;
    if (flag->e_is_true == true) {
        if (flag->i == true) {
            regcomp(&regex, search_strings, REG_ICASE | REG_EXTENDED);
        } else {
            regcomp(&regex, search_strings, REG_EXTENDED);
        }
    } else {
        if (flag->i == true) {
            regcomp(&regex, search_string, REG_ICASE | REG_EXTENDED);
        } else {
            regcomp(&regex, search_string, REG_EXTENDED);
        }
    }
    while (s21_getline(stream, temp_string) != -1) {
        int check_match = 0;

        check_match = regexec(&regex, temp_string, 0, NULL, 0);
        if (flag->void_pattern == true) check_match = 0;
        if (flag->v == true) {
            if (check_match == 0) {
                check_match = 1;
            } else {
                check_match = 0;
            }
        }
        if (flag->c == true && check_match == 0) {
            flag->c_counter++;
        }
        if (check_match == 0 && flag->c == false && flag->l == false) {
            if (flag->n == true || flag->number_of_files >= 2) {
                if (flag->n_print_extented == true ||
                    flag->number_of_files >= 2) {
                    sprintf(temp_string_for_extented_filename,
                            "%s:", flag->filename);
                    printf("%s", temp_string_for_extented_filename);
                }
                if (flag->n == true) {
                    sprintf(temp_string_for_n, "%d:", flag->n_counter);
                    printf("%s", temp_string_for_n);
                }
            }
            printf("%s\n", temp_string);
        }
        if (check_match == 0 && flag->l == true && flag->l_printed == false) {
            flag->l_printed = true;
            printf("%s\n", flag->filename);
        }
        flag->n_counter++;
    }
    if (flag->c == true && flag->c_print_another == false) {
        printf("%d\n", flag->c_counter);
        flag->c_counter = 0;
    }
    if (flag->c == true && flag->c_print_another == true) {
        printf("%s:%d\n", flag->filename, flag->c_counter);
        flag->c_counter = 0;
    }
    regfree(&regex);
}

/* List of errors */

void showError(flags *flag) {
    if (flag->error == 1) {
        fprintf(stderr, "s21_grep %s: No such file or directory\n",
                flag->filename);
    }
    if (flag->error == 2) {
        fprintf(stderr, "grep: invalid option -- %c\n", flag->error_flag);
    }
    if (flag->error == 3) {
        fprintf(stderr, "grep: option requires an argument -- e\n");
    }
    if (flag->error == 1)
        flag->error = 0;  // Obnulenie esli oshibka faila ili smert programmi
}

/* Read string in files */

int s21_getline(FILE *stream, char *temp_string) {
    int current = 0;
    bool none_void = false;
    while ((current = fgetc(stream)) != EOF) {
        none_void = true;
        if (current == 10) break;
        *temp_string = current;
        temp_string++;
    }
    *temp_string = '\0';
    return none_void == true ? 1 : -1;
}

/* Init flags */

void init_flags(flags *flag) {
    flag->e = false;
    flag->i = false;
    flag->v = false;
    flag->c = false;
    flag->l = false;
    flag->n = false;
    flag->error = 0;
    flag->filename = NULL;
    flag->REG_FLAG = 0;
    flag->string_without_e_recorded = false;
    flag->c_counter = 0;
    flag->n_counter = 1;
    flag->l_printed = false;
    flag->c_print_another = false;
    flag->error_flag = 0;
    flag->number_of_files = 0;
    flag->number_of_search_strings = 0;
    flag->n_print_extented = false;
    flag->e_recorded = false;
    flag->e_counter = 0;
    flag->e_is_true = false;
    flag->void_pattern = false;
}
