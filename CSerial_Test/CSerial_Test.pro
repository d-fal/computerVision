#-------------------------------------------------
#
# Project created by QtCreator 2014-12-11T05:24:33
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = CSerial_Test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    serial.cpp \
    controlcommands.cpp

HEADERS += \
    serial.h \
    controlcommands.h

QMAKE_CXXFLAGS += -std=c++11
