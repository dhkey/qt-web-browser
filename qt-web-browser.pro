QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT       += webenginecore webenginewidgets

CONFIG += c++17

TARGET = QtWebBrowser

RESOURCES += resources/resources.qrc

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    tabmanager.cpp

HEADERS += \
    mainwindow.h \
    tabmanager.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
