QT += core gui widgets printsupport

CONFIG += c++17

SOURCES += \
    ../smartcalc_model.cpp \
    ../smartcalc_controller.cpp \
    ../smartcalc_view.cpp \
    credit.cpp \
    deposit.cpp \
    main.cpp \
    mainwindow.cpp
    qcustomplot.cpp

HEADERS += \
    ../smartcalc_model.h \
    ../smartcalc_controller.h \
    ../smartcalc_view.h \
    credit.h \
    deposit.h \
    mainwindow.h
    qcustomplot.h

FORMS += \
    credit.ui \
    deposit.ui \
    mainwindow.ui

TARGET = smartcalc
