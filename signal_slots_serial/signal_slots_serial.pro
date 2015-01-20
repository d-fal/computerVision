#-------------------------------------------------
#
# Project created by QtCreator 2014-12-14T04:44:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = signal_slots_serial
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    person.cpp \
    watercooler.cpp \
    serial.cpp

HEADERS  += mainwindow.h \
    person.h \
    watercooler.h \
    serial.h

FORMS    += mainwindow.ui
