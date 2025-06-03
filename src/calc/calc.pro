QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20
QMAKE_QMAKE = /Users/nikitapotapov/Qt/5.15.16/macos/bin/qmake

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 5.15.16

SOURCES += \
    ../smartcalc_controller.cpp \
    ../smartcalc_model.cpp \
    ../smartcalc_view.cpp \
    credit.cpp \
    deposit.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    ../smartcalc_controller.h \
    ../smartcalc_model.h \
    ../smartcalc_view.h \
    credit.h \
    deposit.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    credit.ui \
    deposit.ui \
    mainwindow.ui

INCLUDEPATH += /Users/nikitapotapov/Qt5.15.16/include \
               /Users/nikitapotapov/Qt5.15.16/lib/QtCore.framework/Versions/5/Headers \
               /Users/nikitapotapov/Qt5.15.16/lib/QtGui.framework/Versions/5/Headers \
               /Users/nikitapotapov/Qt5.15.16/lib/QtWidgets.framework/Versions/5/Headers

LIBS += -F/Users/nikitapotapov/Qt5.15.16/lib \
        -framework QtCore \
        -framework QtGui \
        -framework QtWidgets \
        -framework QtPrintSupport

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
