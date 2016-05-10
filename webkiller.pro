#-------------------------------------------------
#
# Project created by QtCreator 2016-05-09T18:54:39
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = webkiller
TEMPLATE = app

INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib -lpcap

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
