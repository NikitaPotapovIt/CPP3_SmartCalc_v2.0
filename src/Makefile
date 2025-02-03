.PHONY: all clean install uninstall dist tests gcov_report open calc_build main_build

# 🔹 Определение платформы (macOS или Linux)
OS := $(shell uname -s)

ifeq ($(OS), Darwin)  # macOS
    QT_PATH = /Users/nikitapotapov/Qt5.15.16
    LIB_PATHS = -F$(QT_PATH)/lib -L$(QT_PATH)/lib
    LIBS = -framework QtCore -framework QtWidgets -framework QtGui -framework QtPrintSupport
    MOC = $(QT_PATH)/bin/moc
    UIC = $(QT_PATH)/bin/uic
else  # Linux
    QT_PATH = /usr
    LIB_PATHS = -L$(QT_PATH)/lib
    LIBS = -lQt5Core -lQt5Widgets -lQt5Gui -lQt5PrintSupport
    MOC = $(QT_PATH)/bin/moc
    UIC = $(QT_PATH)/bin/uic
endif

INCLUDE_PATHS = -I$(QT_PATH)/include \
                -I$(QT_PATH)/lib/QtCore.framework/Headers \
                -I$(QT_PATH)/lib/QtWidgets.framework/Headers \
                -I$(QT_PATH)/lib/QtGui.framework/Headers \
                -Iqcustomplot.h \
                -Icalc
CC = clang++
CFLAGS = -Wall -Wextra -Werror -std=c++17 $(INCLUDE_PATHS)
LDFLAGS = $(LIB_PATHS) $(LIBS)

SRC_FILES = smartcalc_model.cpp \
            smartcalc_controller.cpp \
            smartcalc_view.cpp \
            calc/credit.cpp \
            calc/deposit.cpp \
            calc/main.cpp \
            calc/mainwindow.cpp \
            calc/qcustomplot.cpp
OBJ_FILES = smartcalc_model.o smartcalc_controller.o smartcalc_view.o \
            calc/credit.o calc/deposit.o calc/main.o calc/mainwindow.o \
            calc/qcustomplot.o calc/moc_qcustomplot.o

UI_FILES = calc/credit.ui calc/deposit.ui calc/mainwindow.ui
GENERATED_UI_HEADERS = $(UI_FILES:.ui=.h)

MOC_FILES = calc/moc_credit.cpp calc/moc_deposit.cpp calc/moc_mainwindow.cpp
TARGET = calc/smartcalc

# 🔹 Основная цель
all: calc_build main_build

# 🔹 Генерация `Makefile` для `calc`, если его нет
calc/Makefile:
	cd calc && qmake calc.pro

# 🔹 Сборка `calc`
calc_build: calc/Makefile $(GENERATED_UI_HEADERS)
	$(MAKE) -C calc -j$(shell nproc || sysctl -n hw.ncpu)

# 🔹 Сборка `src`
main_build: $(TARGET)

$(TARGET): $(OBJ_FILES) $(MOC_FILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_FILES) $(MOC_FILES) $(LDFLAGS)

# 🔹 Создание объектных файлов
calc/%.o: calc/%.cpp $(GENERATED_UI_HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# 🔹 Генерация `ui_*.h` файлов
calc/ui_%.h: calc/%.ui
	$(UIC) $< -o $@

# 🔹 Генерация `moc_*.cpp` файлов
calc/moc_%.cpp: calc/%.h
	$(MOC) $< -o $@

# 🔹 Установка (копирование в `/usr/local/bin`)
install: $(TARGET)
	mkdir -p /usr/local/bin
	cp $(TARGET) /usr/local/bin/

# 🔹 Удаление установленного файла
uninstall:
	rm -f /usr/local/bin/smartcalc

# 🔹 Архивация проекта
dist:
	mkdir -p Archive_calc_v2.0/src
	cp $(TARGET) Archive_calc_v2.0/src/
	tar cvzf Archive_calc_v2.0.tgz Archive_calc_v2.0
	rm -rf Archive_calc_v2.0

# 🔹 Запуск тестов
tests: $(TARGET)
	./tests/run_tests.sh  # Предполагаем, что у тебя есть `run_tests.sh`

# 🔹 Генерация отчета покрытия кода
gcov_report: $(SRC_FILES)
	$(CC) $(CFLAGS) --coverage $(SRC_FILES) -o $(TARGET) $(LDFLAGS)
	./$(TARGET)
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .
	genhtml gcov_test.info -o report

# 🔹 Открытие отчета
open: gcov_report
	open report/index.html

# 🔹 Полная пересборка
rebuild: clean all

# 🔹 Очистка файлов
clean:
	rm -rf *.o $(TARGET) *.gcno *.gcda gcov_test.info report Archive_calc_v2.0 build \
	    calc/ui_*.h calc/moc_*.cpp calc/moc_*.h calc/*.o calc/Makefile calc/calc.app calc/.qmake.stash
