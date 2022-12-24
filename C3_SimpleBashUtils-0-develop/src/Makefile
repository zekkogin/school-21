CC=gcc
CFLAGS= -Wall -Werror -Wextra -std=c11
EXE_GREP=s21_grep
EXE_CAT=s21_cat

all: s21_grep s21_cat

s21_grep: grep/s21_grep.c
	$(CC) $(CFLAGS) grep/s21_grep.c -o grep/$(EXE_GREP)

s21_cat: cat/s21_cat.c
	$(CC) $(CFLAGS) cat/s21_cat.c -o cat/$(EXE_CAT)

check:
#	valgrind -q --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test.out
	python3 ../materials/linters/cpplint.py grep/s21_*.c grep/s21_*.h cat/s21_*.c cat/s21_*.h
	cppcheck --enable=all --suppress=missingIncludeSystem grep/s21_*.c grep/s21_*.h cat/s21_*.c cat/s21_*.h
#	leaks --atExit -- ./test.out | grep LEAK:
	cd ../materials/build/ && sh run.sh 

clean:
	rm grep/s21_grep cat/s21_cat

rebuild: clean all