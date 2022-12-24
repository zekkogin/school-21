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

all: clean s21_decimal.a

main: clean main.o s21_decimal.a
	gcc -o  main_test $(FLAG) main.o s21_decimal.a `pkg-config --cflags --libs check`
	./main_test

test: clean s21_decimal.a check_test.a
	gcc -o test $(FLAG) check_test.a s21_decimal.a `pkg-config --cflags --libs check`
	./test

main.o: main.c
	gcc -c $(FLAG) main.c

s21_decimal.a: 
	gcc -c $(FLAGS) s21_decimal.c s21_decimal_arithmetic.c s21_decimal_convertors.c s21_decimal_comparison.c
	ar rcs s21_decimal.a *.o

check_test.o: 
	gcc -c $(FLAG) decimal_tests.c 

check_test.a: 
	gcc -c $(FLAG) decimal_test_main.c decimal_test_convertors.c decimal_test_arithmetic.c decimal_test_comparison.c decimal_tests.c
	ar rcs check_test.a *.o

decimal_tests.o: decimal_tests.c
	gcc -c $(FLAG) decimal_tests.c

gcov_report: gcov_s21_decimal.a gcov_check_test.a
	gcc -o test $(LIBS) -lgcov check_test.a s21_decimal.a
	./test
	lcov -t 'gcov_report' -o gcov_report.info -c -d .
	genhtml -o gcov_report gcov_report.info

gcov_s21_decimal.a:
	gcc -c $(FLAGS) s21_decimal.c s21_decimal_arithmetic.c s21_decimal_convertors.c s21_decimal_comparison.c --coverage
	ar rcs s21_decimal.a *.o

gcov_test.o:
	gcc -c $(FLAG) decimal_tests.c 
	gcc -o test decimal_tests.o s21_decimal.a $(LIBS) -lgcov

gcov_check_test.a: 
	gcc -c $(FLAG) decimal_test_main.c decimal_test_convertors.c decimal_test_arithmetic.c decimal_test_comparison.c decimal_tests.c
	ar rcs check_test.a *.o

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem .

clean_o:
	rm -rf *.gch *.o

clean:
	rm -rf *.gch *.o *.info *.a *.gcno *.gcda *.png *.html *.css *.txt test_decimal main_test test gcov_report Users


