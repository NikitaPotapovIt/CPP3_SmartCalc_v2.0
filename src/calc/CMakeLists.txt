cmake_minimum_required(VERSION 3.5)

project(calc VERSION 0.1 LANGUAGES CXX)

# Включаем авто-генерацию для .ui и MOC-файлов
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключаем модули Qt
set(Qt6_DIR "/usr/local/Cellar/qt/6.6.0_1/lib/QtWidgets.framework/Versions/A/Headers")
find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui PrintSupport)

# Добавляем исходные файлы проекта
set(PROJECT_SOURCES
main.cpp
mainwindow.cpp
mainwindow.h
mainwindow.ui
../smartcalc_model.cpp
../smartcalc_model.h
../smartcalc_controller.cpp
../smartcalc_controller.h
../smartcalc_view.cpp
../smartcalc_view.h
credit.cpp
credit.h
deposit.cpp
deposit.h
qcustomplot.cpp
qcustomplot.h
)

# Создаем исполняемый файл
qt_add_executable(calc
MANUAL_FINALIZATION
${PROJECT_SOURCES}
)

# Линковка с библиотеками Qt
target_link_libraries(calc PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui Qt6::PrintSupport)
target_include_directories(calc PRIVATE ${CMAKE_SOURCE_DIR})

# Свойства для сборки на macOS и Windows
set_target_properties(calc PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Установка исполняемого файла
include(GNUInstallDirs)
install(TARGETS calc
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Финализация сборки для Qt6
qt_finalize_executable(calc)
