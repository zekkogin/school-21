FLAG = -Wall -Werror -Wextra -g
FLAGS = -std=c11 -g -Wall -Wextra

LIBS_MACOS = -L /usr/local/lib -lcheck
LIBS_LINUX = -lcheck -lsubunit -lpthread -lrt -lm -D_GNU_SOURCE

OS = $(shell uname)
ifeq ($(OS), Darwin)
OPEN = open gcov_report/index.html
LIBS = $(LIBS_MACOS)
LEAK_CHECK = leaks --atExit -- ./test
endif

all: clean s21_calc.a

#test: clean s21_calc.a check_test.a
#	gcc -o test $(FLAG) check_test.a s21_calc.a `pkg-config --cflags --libs check`
#	./test
#
s21_calc.a:
	gcc -c $(FLAGS) getLexems.c help-functions.c lexemsToPostfix.c scanner.c data-structures/Stack.c process.c calculation.c
	ar rcs s21_calc.a *.o
#
#case: clean
#	gcc -o case $(FLAGS) getLexems.c help-functions.c lexemsToPostfix.c scanner.c data-structures/Stack.c main.c calculation.c
#	./case
#
#check_test.a:
#	gcc -c $(FLAG) tests/calc_test.c
#	ar rcs check_test.a *.o
#
#clean_o:
#	rm -rf *.gch *.o
#
clean:
	rm -rf *.gch *.o *.info *.a *.gcno *.gcda *.png *.html *.css *.txt test_matrix main_test test gcov_report Users case a.out
