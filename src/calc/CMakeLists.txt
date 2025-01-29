cmake_minimum_required(VERSION 3.5)

project(calc VERSION 0.1 LANGUAGES CXX)

# Включаем авто-генерацию для .ui, MOC-файлов и ресурсов
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем путь к Qt
set(CMAKE_PREFIX_PATH "/Users/nikitapotapov/Qt/6.8.1/macos/")
set(CMAKE_BINARY_DIR "/Users/nikitapotapov/Documents/Документы_MacBook_Pro_Nikita/School_21/project/CPP3_SmartCalc_v2.0-1/src/calc/build")
set(CMAKE_SOURCE_DIR "/Users/nikitapotapov/Documents/Документы_MacBook_Pro_Nikita/School_21/project/CPP3_SmartCalc_v2.0-1/src/calc")


# Подключаем модули Qt
find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui PrintSupport)

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
qt_add_executable(calc
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

# Линковка с библиотеками Qt
target_link_libraries(calc PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui Qt6::PrintSupport)

# Указываем дополнительные пути для include
target_include_directories(calc PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_AUTOGEN_BUILD_DIR} # Указываем директорию для сгенерированных файлов
    /Users/nikitapotapov/Qt/6.8.1/macos/include
    /Users/nikitapotapov/Qt/6.8.1/macos//lib/QtWidgets.framework/Versions/A/Headers/
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

# Финализация сборки для Qt6
qt_finalize_executable(calc)
