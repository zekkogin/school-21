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

all: clean s21_matrix.a

test: clean s21_matrix.a check_test.a
	gcc -o test $(FLAG) check_test.a s21_matrix.a `pkg-config --cflags --libs check`
	./test

test_alpine: clean s21_matrix.a check_test_alpine.a
	gcc -o test $(FLAG) check_test_alpine.a s21_matrix.a `pkg-config --cflags --libs check`

check_test_alpine.a:
	gcc -c $(FLAG) matrix_test_alpine.c
	ar rcs check_test_alpine.a *.o

s21_matrix.a: 
	gcc -c $(FLAGS) s21_matrix.c
	ar rcs s21_matrix.a *.o

check_test.a: 
	gcc -c $(FLAG) matrix_test.c
	ar rcs check_test.a *.o

gcov_report: clean
	gcc -c $(FLAGS) s21_matrix.c --coverage
	ar rcs gcov_s21_matrix.a *.o

	gcc -c $(FLAGS) matrix_test.c
	gcc -o test_with_gcov matrix_test.o gcov_s21_matrix.a $(LIBS) -lgcov
	./test_with_gcov

	lcov -t 'gcov_report' -o gcov_report.info -c -d .
	genhtml -o gcov_report gcov_report.info
	$(OPEN)

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem .

clean_o:
	rm -rf *.gch *.o

clean:
	rm -rf *.gch *.o *.info *.a *.gcno *.gcda *.png *.html *.css *.txt test_matrix main_test test gcov_report Users
