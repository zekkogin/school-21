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
	open ./$(BUILD_DIR)/3d_viewer.app/Contents/MacOS/3d_viewer

install: clean_cpp
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && qmake ../3d_viewer.pro && make

test: clean_c s21_parser.a check_test.a
	cd $(LOGIC) && gcc -o test $(GFLAGS) pars_test.a parser.a #`pkg -config --cflags --libscheck`
	cd $(LOGIC) && ./test

s21_parser.a:
	cd $(LOGIC) && gcc -c $(FLAGS) matrix_t.c parser.c
	cd $(LOGIC) && ar rcs parser.a *.o

check_test.a:
	cd $(LOGIC) && gcc -c $(FLAGS) pars_test.c
	cd $(LOGIC) && ar rcs pars_test.a *.o

clean_c:
	cd $(LOGIC) && rm -rf *.gch *.o *.info *.a *.gcno *.gcda *.png *.html *.css *.txt test gcov_report Users case a.out

clean: clean_c clean_cpp

clean_cpp:
	rm -rf $(BUILD_DIR)
	rm -rf doc

uninstall: clean_cpp

lint:
	clang-format -i s21_parser.h main.cpp mainwindow.cpp Logic/*.c openglwidget.cpp openglwidget.h

gcov_report: FLAGS += $(GCOV_FLAGS) $(LIBS)

gcov_report: test
	cd $(LOGIC) && lcov -t 'gcov_report' -o gcov_report.info -c -d .
	cd $(LOGIC) && genhtml -o gcov_report gcov_report.info
	cd $(LOGIC) && $(OPEN)

dist:
	rm -rf 3d_release
	mkdir 3d_release
	cp -r Makefile 3d_viewer.pro *.cpp *.ui *.h Logic Doxyfile ./3d_release
	tar cvzf ./3d_release.tgz 3d_release/
	rm -rf 3d_release/
	make clean

dvi: clean
	doxygen Doxyfile
	open doc/html/index.html
	
