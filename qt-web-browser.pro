QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT       += webenginecore webenginewidgets
QT += sql

CONFIG += c++17

TARGET = QtWebBrowser

RESOURCES += resources/resources.qrc

SOURCES += \
    historymanager.cpp \
    historyview.cpp \
    main.cpp \
    mainwindow.cpp \
    tabmanager.cpp

HEADERS += \
    historymanager.h \
    historyview.h \
    mainwindow.h \
    tabmanager.h

FORMS += \
    historyview.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
