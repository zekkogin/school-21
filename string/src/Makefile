.PHONY: s21_string.a s21_stringplus.o
CC=gcc
CFLAGS= -std=c11
GCOV=--coverage
LDFLAGS=-lcheck -lpthread -lm
EXE=test.out
FUNCS=s21_string.c s21_sprintf.c
OBJ=$(FUNCS:.c=.o)
LIBO=s21_string.o
LIBA=s21_string.a
TSTC=s21_stringplus.c
TSTO=s21_stringplus.o

all: s21_string.a

s21_string.a: $(OBJ)
	ar rcs $@ $^
	ranlib $@

.c.o:
	$(CC) -c $< -o $@

test: s21_string.a
	$(CC) $(CFLAGS) $(TSTC) -L. $< $(LDFLAGS) -o ./$(EXE)
	./$(EXE)

clean:
	rm -rf *.info; rm -rf *.gcda; rm -rf *.gcno
	rm -rf *.o; rm -rf *.a
	rm -rf report/ rm rf *.out

rebuild: clean all

s21_stringplus.o:
	$(CC) $(CFLAGS) -c $(TSTC) -o $(TSTO)

check:  clean gcov_report
	valgrind -q --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test.out
	python3 ../materials/linters/cpplint.py --extension=c s21*.c s21*.h
	cppcheck --enable=all --suppress=missingIncludeSystem ./s21_*.c ./s21_*.h
#	leaks --atExit -- ./test.out | grep LEAK:
	cd ../materials/build/ && sh run.sh

gcov_report: $(TSTO) test
	$(CC) $(GCOV) $(FUNCS) $(TSTO) $(LIBA) -L. $(LIBA) $(LDFLAGS) -o ./$(EXE)
	./$(EXE)
	lcov -t "test_coverage" -c -d . -o test_coverage.info --rc lcov_branch_coverage=1
	genhtml -o report test_coverage.info --branch-coverage


