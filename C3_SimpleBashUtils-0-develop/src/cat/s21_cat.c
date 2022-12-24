#include "s21_cat.h"

int main(int argc, char **argv) {
    flags flag = {0};
    flag.number_of_string = 1;
    flag.number_of_non_void_string = 1;
    if (argc > 1) {
        for (int counter = 1; counter < argc; counter++) {
            if (argv[counter][0] == '-' && argv[counter][1] != '-' &&
                flag.stop == false) {
                int length = strlen(argv[counter]);
                for (int i = 1; i < length; i++) {
                    if (argv[counter][i] == '-') {
                        flag.stop = true;
                    } else if (argv[counter][i] == 'b') {
                        flag.b = true;
                    } else if (argv[counter][i] == 'e') {
                        flag.e = true;
                    } else if (argv[counter][i] == 'n') {
                        flag.n = true;
                    } else if (argv[counter][i] == 's') {
                        flag.s = true;
                    } else if (argv[counter][i] == 't') {
                        flag.t = true;
                    } else if (argv[counter][i] == 'v') {
                        flag.v = true;
                    } else if (argv[counter][i] == 'T') {
                        flag.T = true;
                    } else if (argv[counter][i] == 'E') {
                        flag.E = true;
                    } else {
                        flag.error = 2;
                        flag.wrongflag = argv[counter][i];
                    }
                }
            } else {
                if (strcmp(argv[counter], "--number-nonblank") == 0)
                    flag.b = true;
                if (strcmp(argv[counter], "--squeeze-blank") == 0)
                    flag.s = true;
                if (strcmp(argv[counter], "--number") == 0) flag.n = true;
                if (strcmp(argv[counter], "--show-nonprinting") == 0)
                    flag.v = true;
            }
            if (argv[counter][0] != '-') {
                FILE *stream;
                stream = fopen(argv[counter], "r");
                if (stream == NULL && flag.error != 2) {
                    flag.error = 1;
                    flag.filename = argv[counter];
                }
                if (flag.error == 0) {
                    taskPrint(stream, &flag);
                    fclose(stream);
                } else {
                    showError(&flag);
                }
            }
        }
    }
    return flag.error == 0 ? 0 : flag.error;
}

void taskPrint(FILE *stream, flags *flag) {
    if (flag->b == true) flag->n = false;  //  priority b > n
    if (flag->e == true || flag->t == true) flag->v = true;
    int current = 0;
    bool newline = true;
    bool test = true;
    int counter = 0;
    while ((current = fgetc(stream)) != EOF) {
        counter++;
        int future = 0;
        if (flag->s == true && newline == true) {
            future = current;
            if (future == 10) {
                while (future == 10) {
                    future = fgetc(stream);
                    if (feof(stream))
                        test = false;  // проверка на пустую строку в конце,
                                       // иначе fseek зацикливает чтение
                }
                if (test) fseek(stream, -1, SEEK_CUR);
            }
        }
        if (flag->n == true && newline == true) {
            printf("%6d\t", flag->number_of_string);
            flag->number_of_string++;
        }
        if (flag->b == true && newline == true) {
            future = fgetc(stream);
            if (feof(stream) == 0) {
                if ((current == 10 && future == 10) ||
                    (current == 10 && future != 10)) {
                    fseek(stream, -1, SEEK_CUR);
                } else {
                    fseek(stream, -1, SEEK_CUR);
                    printf("%6d\t", flag->number_of_non_void_string);
                    flag->number_of_non_void_string++;
                }
            }
        }
        if (flag->t == true || flag->T == true) {
            if (current == 9) {
                current = 94;
                putchar(current);
                current = 73;
            }
        }
        if (flag->v == true) {
            if (current <= 31 && current != 9 && current != 10 &&
                current != 13) {
                putchar(94);
                current = current + 64;
            }
            if (current == 127) {
                putchar(94);
                current = current - 64;
            }
        }
        if (current == 10)
            newline = true;
        else
            newline = false;
        if ((flag->e == true || flag->E == true) && newline == true &&
            counter >= 1) {
            fseek(stream, -1, SEEK_CUR);
            current = 36;
            putchar(current);
            current = fgetc(stream);
        }
        putchar(current);
    }
}

void showError(flags *flag) {
    if (flag->error == 1) {
        printf("cat: %s: No such file or directory\n", flag->filename);
    }
    if (flag->error == 2) {
        printf("cat: illegal option -- %c\nusage: cat [-benstuv] [file ...]",
               flag->wrongflag);
    }
}
