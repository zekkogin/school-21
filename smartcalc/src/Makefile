FLAG = -Wall -Werror -Wextra -g
FLAGS = -std=c11 -g -Wall -Wextra
GCOV_FLAGS = -fprofile-arcs -ftest-coverage #-lgcov
LOGIC = Logic/
LIBS_MACOS = -L /usr/local/lib -lcheck
LIBS = -lcheck -lsubunit -lpthread -lrt -lm -D_GNU_SOURCE
BUILD_DIR = Build
OPEN = firefox gcov_report/index.html
GFLAGS = $(FLAGS) $(GCOV_FLAGS) $(LIBS)

OS := $(shell uname)

ifeq ($(OS), Darwin)
	OPEN = open gcov_report/index.html
	LIBS = $(LIBS_MACOS)
endif

all: install
	open ./$(BUILD_DIR)/Calculator.app/Contents/MacOS/Calculator

install: clean_cpp
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && qmake ../Calculator.pro && make

test: clean_c s21_calc.a check_test.a
	cd $(LOGIC) && gcc -o test $(GFLAGS) check_test.a s21_calc.a #`pkg -config --cflags --libscheck`
	cd $(LOGIC) && ./test

s21_calc.a:
	cd $(LOGIC) && gcc -c $(FLAGS) getLexems.c help-functions.c lexemsToPostfix.c scanner.c Stack.c process.c calculation.c
	cd $(LOGIC) && ar rcs s21_calc.a *.o

case: clean_c
	cd $(LOGIC) && gcc -o case $(FLAGS) getLexems.c help-functions.c lexemsToPostfix.c scanner.c Stack.c main.c calculation.c
	cd $(LOGIC) && ./case

check_test.a:
	cd $(LOGIC) && gcc -c $(FLAGS) calc_test.c
	cd $(LOGIC) && ar rcs check_test.a *.o

clean_c:
	cd $(LOGIC) && rm -rf *.gch *.o *.info *.a *.gcno *.gcda *.png *.html *.css *.txt test gcov_report Users case a.out

clean: clean_c clean_cpp

clean_cpp:
	rm -rf $(BUILD_DIR)
	rm -rf doc

uninstall: clean_cpp

lint:
	clang-format -i s21_calc.h main.cpp mainwindow.cpp Logic/*.c

gcov_report: FLAGS += $(GCOV_FLAGS) $(LIBS)

gcov_report: test
	cd $(LOGIC) && lcov -t 'gcov_report' -o gcov_report.info -c -d .
	cd $(LOGIC) && genhtml -o gcov_report gcov_report.info
	cd $(LOGIC) && $(OPEN)

dist:
	rm -rf calc_release
	mkdir calc_release
	cp -r Makefile Calculator.pro *.cpp *.ui *.h Logic Doxyfile ./calc_release
	tar cvzf ./calc_release.tgz calc_release/
	rm -rf calc_release/
	make clean

dvi: clean
	doxygen Doxyfile
	open doc/html/index.html
	
