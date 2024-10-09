.PHONY: all test clean rebuild dist install uninstall gcov_report open check

CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17
SRC_FILES = smartcalc_model.cpp smartcalc_controller.cpp smartcalc_view.cpp main.cpp
OBJ_FILES = $(SRC_FILES:.cpp=.o)
LIB = -lm

all: smartcalc

smartcalc: $(OBJ_FILES)
	$(CC) $(CFLAGS) -o smartcalc $(OBJ_FILES) $(LIB)

test: smartcalc
	./smartcalc

dist:
	rm -rf Archive_calc_v1.0/
	mkdir Archive_calc_v1.0/
	mkdir Archive_calc_v1.0/src/
	cp -r ./smartcalc Archive_calc_v1.0/src/
	tar cvzf Archive_calc_v1.0.tgz Archive_calc_v1.0/
	rm -rf Archive_calc_v1.0/

install:
	mkdir build
	cp smartcalc build/smartcalc

uninstall:
	rm -rf build

gcov_report: gcov_test.info

gcov_test.info: gcov_test gcov_test.gcda
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .

gcov_test: $(SRC_FILES)
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage $(SRC_FILES) -o gcov_test $(LIB)

open: gcov_report
	open report/index.html

rebuild: clean all

clean:
	@rm -rf *.o smartcalc
	@rm -rf Archive_calc_v1.0
	@rm -rf *.tgz
	@rm -rf build
	@rm -rf *.gcno
	@rm -rf *.gcda
