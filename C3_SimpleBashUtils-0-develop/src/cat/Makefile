CC=gcc
CFLAGS= -Wall -Werror -Wextra -std=c11
EXE=s21_cat

all: s21_cat

s21_cat: s21_cat.c
	$(CC) $(CFLAGS) s21_cat.c -o $(EXE)

clean:
	rm s21_cat

rebuild: clean all