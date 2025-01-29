.PHONY: all clean dist test install uninstall rebuild gcov_report open calc_build main_build

QT_PATH = /Users/nikitapotapov/Qt/6.8.1/macos
QT_PATH_F = -F$(QT_PATH)
INCLUDE_PATHS = -I$(QT_PATH)/lib/QtWidgets.framework/Headers \
                -I$(QT_PATH)/lib/QtCore.framework/Headers \
                -I$(QT_PATH)/lib/QtGui.framework/Headers \
                -Icalc
LIB_PATHS = -L$(QT_PATH)/lib
LIBS = -framework QtCore -framework QtWidgets -framework QtGui -framework QtPrintSupport
CC = clang++
CFLAGS = -Wall -Wextra -Werror -std=c++17 $(INCLUDE_PATHS)
LDFLAGS = $(LIB_PATHS) $(LIBS)

SRC_FILES = smartcalc_model.cpp \
            smartcalc_controller.cpp \
            smartcalc_view.cpp \
            calc/credit.cpp \
            calc/deposit.cpp \
            calc/main.cpp \
            calc/mainwindow.cpp
OBJ_FILES = $(SRC_FILES:.cpp=.o)
UI_FILES = calc/credit.ui calc/deposit.ui
GENERATED_UI_HEADERS = $(UI_FILES:.ui=.h)
TARGET = calc/smartcalc

# Основная цель
all: calc_build main_build

# Сборка в директории calc
calc_build:
	$(MAKE) -C calc

# Сборка основного проекта
main_build: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_FILES) $(LDFLAGS)

# Создание объектных файлов
calc/%.o: calc/%.cpp $(GENERATED_UI_HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Генерация ui_*.h файлов
calc/ui_%.h: calc/%.ui
	$(QT_PATH)/libexec/uic $< -o $@

# Очистка
clean:
	rm -rf *.o $(TARGET) *.gcno *.gcda gcov_test.info report Archive_calc_v2.0 build \
	    calc/ui_*.h calc/*.o