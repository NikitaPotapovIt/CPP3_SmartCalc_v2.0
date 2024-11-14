cmake_minimum_required(VERSION 3.5)

project(calc VERSION 0.1 LANGUAGES CXX)

# Включаем авто-генерацию для .ui и MOC-файлов
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Поиск библиотеки Qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core Gui PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core Gui PrintSupport)

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

# Определение целевого приложения с учетом версии Qt
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(calc
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(calc
        ${PROJECT_SOURCES}
    )
endif()

# Линковка с библиотеками Qt
target_link_libraries(calc PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Свойства для сборки на macOS и Windows
set_target_properties(calc PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Установка исполняемого файла в стандартные директории
include(GNUInstallDirs)
install(TARGETS calc
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Финализируем сборку для Qt6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(calc)
endif()
