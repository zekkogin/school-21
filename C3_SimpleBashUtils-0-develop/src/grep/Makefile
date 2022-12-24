CC=gcc
CFLAGS= -Wall -Werror -Wextra -std=c11
EXE_GREP=s21_grep

all: s21_grep

s21_grep: s21_grep.c
	$(CC) $(CFLAGS) s21_grep.c -o $(EXE_GREP)

clean:
	rm s21_grep

rebuild: clean all