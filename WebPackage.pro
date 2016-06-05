#-------------------------------------------------
#
# Project created by QtCreator 2016-05-09T18:54:39
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = webpackage
TEMPLATE = app

INCLUDEPATH += /usr/local/Cellar/libpcap/1.7.4/include
LIBS += -L/usr/local/Cellar/libpcap/1.7.4/lib -lpcap

SOURCES += main.cpp\
        mainwindow.cpp \
    Capture/captureform.cpp \
    Pressure/pressureform.cpp \
    Capture/utilscapture.cpp

HEADERS  += mainwindow.h \
    Capture/captureform.h \
    Pressure/pressureform.h \
    Capture/utilscapture.h

FORMS    += mainwindow.ui \
    Capture/captureform.ui \
    Pressure/pressureform.ui

DISTFILES += \
    README.md
