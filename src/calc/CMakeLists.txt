cmake_minimum_required(VERSION 3.10)

project(calc VERSION 0.1 LANGUAGES CXX)

# Включаем авто-генерацию для .ui, MOC-файлов и ресурсов
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем путь к Qt
set(CMAKE_PREFIX_PATH "/Users/nikitapotapov/Qt5.15.16")

# Подключаем модули Qt
find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui PrintSupport)

# Указываем пути для автогенерации (в одной директории)
set(CMAKE_AUTOGEN_BUILD_DIR ${CMAKE_BINARY_DIR}/autogen)
set(CMAKE_AUTOUIC_OUTPUT_DIRECTORY ${CMAKE_AUTOGEN_BUILD_DIR})
set(CMAKE_AUTOMOC_OUTPUT_DIRECTORY ${CMAKE_AUTOGEN_BUILD_DIR})
set(CMAKE_AUTORCC_OUTPUT_DIRECTORY ${CMAKE_AUTOGEN_BUILD_DIR})

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
target_link_libraries(calc PRIVATE Qt5::Widgets Qt5::Core Qt5::Gui Qt5::PrintSupport)

# Указываем дополнительные пути для include
target_include_directories(calc PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_AUTOGEN_BUILD_DIR} # Указываем директорию для сгенерированных файлов
    /Users/nikitapotapov/Qt5.15.16
    /Users/nikitapotapov/Qt5.15.16/lib/QtWidgets.framework
)

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
