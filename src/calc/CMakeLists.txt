cmake_minimum_required(VERSION 3.10)
project(calc VERSION 0.1 LANGUAGES CXX)

# Включаем авто-генерацию для .ui, MOC-файлов и ресурсов
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем путь к Qt (с возможностью переопределения)
set(CMAKE_PREFIX_PATH "/Users/nikitapotapov/Qt5.15.16" CACHE PATH "Path to Qt installation")

# Подключаем модули Qt
find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui PrintSupport)

# Проверяем, что Qt найден
if(NOT Qt5_FOUND)
    message(FATAL_ERROR "Qt5 не найден! Укажите правильный путь в CMAKE_PREFIX_PATH.")
endif()

# Предполагаем, что CMakeLists.txt находится в calc/, а smartcalc_* в ../
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
    credit.ui
    deposit.cpp
    deposit.h
    deposit.ui
    qcustomplot.cpp
    qcustomplot.h
)

# Создаем исполняемый файл
add_executable(calc ${PROJECT_SOURCES})

# Линковка с библиотеками Qt
target_link_libraries(calc PRIVATE
    Qt5::Widgets
    Qt5::Core
    Qt5::Gui
    Qt5::PrintSupport
)

# Указываем дополнительные пути для include
target_include_directories(calc PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}  # Для файлов в calc/
    ${CMAKE_SOURCE_DIR}          # Для файлов в корне проекта (smartcalc_*)
)

# Свойства для сборки на macOS
set_target_properties(calc PROPERTIES
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_GUI_IDENTIFIER "com.example.smartcalc"
    MACOSX_BUNDLE_BUNDLE_NAME "SmartCalc"
)

# Установка исполняемого файла
include(GNUInstallDirs)
install(TARGETS calc
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Поддержка покрытия кода
option(ENABLE_COVERAGE "Enable code coverage" OFF)
if(ENABLE_COVERAGE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        add_compile_options(--coverage)
        add_link_options(--coverage)
    else()
        message(WARNING "Coverage is only supported with Clang.")
    endif()
endif()
