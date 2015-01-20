#-------------------------------------------------
#
# Project created by QtCreator 2014-12-08T20:23:33
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = openGL_test02
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp

HEADERS  += mainwindow.h \
    glwidget.h

FORMS    += mainwindow.ui

INCLUDEPATH += C:\\Qt\\glut

LIBS += -lglut
LIBS += -lglut32

