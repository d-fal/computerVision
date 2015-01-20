#-------------------------------------------------
#
# Project created by QtCreator 2014-12-10T17:30:30
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = RS232_test_03
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    txrxfuncs.cpp \
    rs232connection.cpp

HEADERS += \
    txrxfuncs.h \
    rs232connection.h

QMAKE_CXXFLAGS += -std=c++11
