#-------------------------------------------------
#
# Project created by QtCreator 2016-05-09T18:54:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = webkiller
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Capture/captureform.cpp \
    Pressure/pressureform.cpp

HEADERS  += mainwindow.h \
    Capture/captureform.h \
    Pressure/pressureform.h

FORMS    += mainwindow.ui \
    Capture/captureform.ui \
    Pressure/pressureform.ui
