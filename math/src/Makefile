FLAGS = -std=c11 -g -Wall -Wextra
ASAN = #-fsanitize=address

LIBS_MACOS = -L /usr/local/lib -lcheck
LIBS_LINUX = -lcheck -lsubunit -lpthread -lrt -lm -D_GNU_SOURCE

OS = $(shell uname)
ifeq ($(OS), Darwin)
OPEN = open gcov_report/index.html
LIBS = $(LIBS_MACOS)
LEAK_CHECK = leaks --atExit -- ./test
endif

ifeq ($(OS), Linux)
OPEN = open gcov_report/index.html
LIBS = $(LIBS_LINUX)
LEAK_CHECK = valgrind --leak-check=full --show-leak-kinds=all -s ./test
endif

all: clean s21_math.a

test: clean s21_math.a
	gcc -c $(FLAGS) $(ASAN) s21_test.c
	gcc -o test $(ASAN) *.o $(LIBS)
	./test

s21_math.a:
	gcc -c $(FLAGS) $(ASAN) s21_math.c
	ar rcs s21_math.a s21*.o
	cp s21_math.a libs21_math.a

gcov_report: clean
	gcc -c $(FLAGS) s21_math.c --coverage
	ar rcs gcov_s21_math.a *.o

	gcc -c $(FLAGS) s21_test.c
	gcc -o test_with_gcov s21_test.o gcov_s21_math.a $(LIBS) -lgcov
	./test_with_gcov

	lcov -t 'gcov_report' -o gcov_report.info -c -d .
	genhtml -o gcov_report gcov_report.info
	$(OPEN)

check:
	cppcheck —enable=all —suppress=missingIncludeSystem ../src/
	CK_FORK=no leaks -atExit -- ./test

clean:
	rm -rf *.o
	rm -rf *.a
	rm -rf test test_with_gcov
	rm -rf *.gcno *.gcda *.info
	rm -rf gcov_report
