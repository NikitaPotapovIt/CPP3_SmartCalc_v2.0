.PHONY: all clean install uninstall dist tests gcov_report open calc_build main_build rebuild clean_tests prepare_gcov generate_ui dvi

# Отключаем параллельное выполнение для gcov_report
.NOTPARALLEL: gcov_report

# 🔹 Определение платформы (macOS или Linux)
OS := $(shell uname -s)

ifeq ($(OS), Darwin)  # macOS
    QT_PATH = /Users/nikitapotapov/Qt5.15.16
    LIB_PATHS = -F$(QT_PATH)/lib -L$(QT_PATH)/lib
    LIBS = -framework QtCore -framework QtWidgets -framework QtGui -framework QtPrintSupport
    MOC = $(QT_PATH)/bin/moc
    UIC = $(QT_PATH)/bin/uic
	INSTALL_DIR = /Applications
    APP_NAME = calc.app
else  # Linux
    QT_PATH = /usr
    LIB_PATHS = -L$(QT_PATH)/lib
    LIBS = -lQt5Core -lQt5Widgets -lQt5Gui -lQt5PrintSupport
    MOC = $(QT_PATH)/bin/moc
    UIC = $(QT_PATH)/bin/uic
	INSTALL_DIR = /usr/local/bin
    APP_NAME = smartcalc
endif

INCLUDE_PATHS = -I$(QT_PATH)/include \
                -I$(QT_PATH)/include/QtCore \
                -I$(QT_PATH)/include/QtWidgets \
                -I$(QT_PATH)/include/QtGui \
                -I$(QT_PATH)/lib/QtCore.framework/Versions/5/Headers \
                -I$(QT_PATH)/lib/QtWidgets.framework/Versions/5/Headers \
                -I$(QT_PATH)/lib/QtGui.framework/Versions/5/Headers \
                -I. -Icalc
CC = clang++
CFLAGS = -Wall -Wextra -Werror -std=c++20
LDFLAGS = $(LIB_PATHS) $(LIBS)
LFLAGS = -lgtest_main -lgtest -lpthread

# 🔹 Исходные файлы и объектные файлы
SRC_FILES = smartcalc_model.cpp \
            smartcalc_controller.cpp \
            smartcalc_view.cpp \
            calc/credit.cpp \
            calc/deposit.cpp \
            calc/main.cpp \
            calc/mainwindow.cpp \
            calc/qcustomplot.cpp
OBJ_FILES = $(SRC_FILES:.cpp=.o)
UI_FILES = calc/credit.ui calc/deposit.ui calc/mainwindow.ui
GENERATED_UI_HEADERS = calc/ui_credit.h calc/ui_deposit.h calc/ui_mainwindow.h
MOC_FILES = calc/moc_credit.cpp calc/moc_deposit.cpp calc/moc_mainwindow.cpp calc/moc_qcustomplot.cpp
MOC_OBJ_FILES = $(MOC_FILES:.cpp=.o)
TARGET = calc/smartcalc

# 🔹 Тестовые файлы
TEST_SRC = test.cpp smartcalc_model.cpp
TEST_OBJ = $(TEST_SRC:.cpp=.o)
TEST_TARGET = test_runner

# 🔹 Основная цель (с запуском калькулятора)
all: calc_build main_build
	./$(TARGET)

# 🔹 Генерация `Makefile` для `calc`, если его нет
calc/Makefile:
	cd calc && qmake calc.pro

# 🔹 Сборка `calc` через qmake (без покрытия)
calc_build: calc/Makefile $(GENERATED_UI_HEADERS)
	$(MAKE) -C calc -j$(shell nproc || sysctl -n hw.ncpu)

# 🔹 Сборка основного приложения (без покрытия)
main_build: $(TARGET)

$(TARGET): $(OBJ_FILES) $(MOC_OBJ_FILES)
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) $(OBJ_FILES) $(MOC_OBJ_FILES) -o $@ $(LDFLAGS)
ifeq ($(OS), Darwin)
	install_name_tool -add_rpath $(QT_PATH)/lib $@
endif

# 🔹 Создание объектных файлов для исходников (без покрытия)
%.o: %.cpp $(GENERATED_UI_HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) -c $< -o $@

# 🔹 Создание объектных файлов для Moc-файлов (без покрытия)
calc/moc_%.o: calc/moc_%.cpp
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) -c $< -o $@

# 🔹 Явные правила для генерации `ui_*.h` файлов
calc/ui_credit.h: calc/credit.ui
	$(UIC) $< -o $@
	@echo "Generated: $@"

calc/ui_deposit.h: calc/deposit.ui
	$(UIC) $< -o $@
	@echo "Generated: $@"

calc/ui_mainwindow.h: calc/mainwindow.ui
	$(UIC) $< -o $@
	@echo "Generated: $@"

# 🔹 Генерация `moc_*.cpp` файлов
calc/moc_qcustomplot.cpp: calc/qcustomplot.h
	$(MOC) $< -o $@
	@echo "Generated MOC file: $@"
calc/moc_credit.cpp: calc/credit.h
	$(MOC) $< -o $@
	@echo "Generated MOC file: $@"
calc/moc_deposit.cpp: calc/deposit.h
	$(MOC) $< -o $@
	@echo "Generated MOC file: $@"
calc/moc_mainwindow.cpp: calc/mainwindow.h
	$(MOC) $< -o $@
	@echo "Generated MOC file: $@"

# 🔹 Сборка и запуск тестов (без покрытия)
tests: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) -o $@ $(LFLAGS)

# 🔹 Генерация отчета покрытия кода с gcovr
gcov_report: clean generate_ui prepare_gcov $(TEST_TARGET)_gcov
	./$(TEST_TARGET)_gcov  # Запуск тестов с покрытием
	@if ! command -v gcovr &> /dev/null; then \
		echo "Error: gcovr is not installed. Install it with 'pip install gcovr'"; \
		exit 1; \
	fi
	mkdir -p report  # Создаем директорию report, если ее нет
	gcovr --html --html-details --output report/index.html \
		--exclude '.*moc_.*' \
    	--exclude '.*ui_.*' \
    	--exclude '.*/qt/.*' \
    	--exclude 'calc/qcustomplot\.cpp' \
    	--exclude 'calc/mainwindow\.cpp' \
    	--exclude 'calc/credit\.cpp' \
    	--exclude 'calc/deposit\.cpp' \
    	--print-summary
	@echo "Report generated: report/index.html"
	open report/index.html

# 🔹 Сборка тестов с покрытием
$(TEST_TARGET)_gcov: $(TEST_SRC:.cpp=_gcov.o)
	$(CC) $(CFLAGS) --coverage $(INCLUDE_PATHS) $^ -o $@ $(LDFLAGS) $(LFLAGS)
ifeq ($(OS), Darwin)
	install_name_tool -add_rpath $(QT_PATH)/lib $@
endif

# 🔹 Создание объектных файлов с покрытием
%_gcov.o: %.cpp $(GENERATED_UI_HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) --coverage -c $< -o $@

calc/moc_%_gcov.o: calc/moc_%.cpp
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) --coverage -c $< -o $@

# 🔹 Подготовка для gcov (генерация moc_*.cpp)
prepare_gcov: $(MOC_FILES)

# 🔹 Генерация ui_*.h
generate_ui: $(GENERATED_UI_HEADERS)

# 🔹 Установка приложения
install: calc_build
ifeq ($(OS), Darwin)
	mkdir -p $(INSTALL_DIR)
	cp -r calc/$(APP_NAME) $(INSTALL_DIR)/
	@echo "Application installed to $(INSTALL_DIR)/$(APP_NAME)"
else
	mkdir -p $(INSTALL_DIR)
	cp $(TARGET) $(INSTALL_DIR)/$(APP_NAME)
	@echo "Application installed to $(INSTALL_DIR)/$(APP_NAME)"
endif

# 🔹 Удаление приложения
uninstall:
ifeq ($(OS), Darwin)
	rm -rf $(INSTALL_DIR)/$(APP_NAME) $(TARGET) calc/calc.app
	@echo "Application uninstalled from $(INSTALL_DIR)/$(APP_NAME)"
else
	rm -f $(INSTALL_DIR)/$(APP_NAME)
	@echo "Application uninstalled from $(INSTALL_DIR)/$(APP_NAME)"
endif

# 🔹 Создание дистрибутива
dist: calc_build
	mkdir -p dist/calc_v2.0
	cp -r $(SRC_FILES) calc/*.h calc/*.ui calc/calc.pro dist/calc_v2.0/
ifeq ($(OS), Darwin)
	cp -r calc/$(APP_NAME) dist/calc_v2.0/
else
	cp $(TARGET) dist/calc_v2.0/
endif
	tar -czf calc_v2.0.tar.gz -C dist calc_v2.0
	rm -rf dist
	@echo "Distribution archive created: calc_v2.0.tar.gz"

dvi:
	open report/index.html

# 🔹 Очистка файлов
clean:
	rm -rf *.o $(TARGET) *.gcno *.gcda *.profraw *.profdata report Archive_calc_v2.0* build \
	    calc/ui_*.h calc/moc_*.cpp calc/moc_*.h calc/*.o calc/Makefile calc/calc.app report.* calc_v2.0.tar.gz \
	    calc/.qmake.stash test_runner calc/*.gcno calc/*.gcda coverage.info *_gcov.o calc/smartcalc_gcov $(TEST_TARGET)_gcov

# 🔹 Очистка тестов
clean_tests:
	rm -f $(TEST_OBJ) $(TEST_TARGET)

# 🔹 Полная пересборка
rebuild: clean all
