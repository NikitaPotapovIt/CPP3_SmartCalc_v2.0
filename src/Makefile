.PHONY: all clean dist test install uninstall rebuild gcov_report open

CC = g++
# CFLAGS = -Wall -Wextra -Werror -std=c++17 -I/Users/nikitapotapov/Qt/6.6.2/macos/lib
# LDFLAGS = `pkg-config --libs Qt6Core Qt6Gui Qt6Widgets`
CFLAGS = -Wall -Wextra -Werror -std=c++17 \
         -I/Users/nikitapotapov/Qt/6.6.2/macos/lib/QtWidgets.framework/Headers \
         -I/Users/nikitapotapov/Qt/6.6.2/macos/lib/QtCore.framework/Headers \
         -I/Users/nikitapotapov/Qt/6.6.2/macos/lib/QtGui.framework/Headers
LDFLAGS = -L/Users/nikitapotapov/Qt/6.6.2/macos/lib -framework QtCore -framework QtWidgets -framework QtGui -framework QtPrintSupport
SRC_FILES = smartcalc_model.cpp \
            smartcalc_controller.cpp \
            smartcalc_view.cpp \
            ./calc/credit.cpp \
            ./calc/deposit.cpp \
            ./calc/main.cpp \
            ./calc/mainwindow.cpp
OBJ_FILES = $(SRC_FILES:.cpp=.o)
TARGET = smartcalc

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_FILES) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TARGET)
	./$(TARGET)

dist:
	mkdir -p Archive_calc_v2.0/src
	cp $(TARGET) Archive_calc_v2.0/src/
	tar cvzf Archive_calc_v2.0.tgz Archive_calc_v2.0
	rm -rf Archive_calc_v2.0

install:
	mkdir -p build
	cp $(TARGET) build/

uninstall:
	rm -rf build

gcov_report: $(SRC_FILES)
	$(CC) $(CFLAGS) --coverage $(SRC_FILES) -o $(TARGET) $(LDFLAGS)
	./$(TARGET)
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .
	genhtml gcov_test.info -o report

open: gcov_report
	open report/index.html

rebuild: clean all

clean:
	rm -rf *.o $(TARGET) *.gcno *.gcda gcov_test.info report Archive_calc_v2.0 build
