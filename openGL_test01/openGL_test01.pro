#-------------------------------------------------
#
# Project created by QtCreator 2014-12-08T15:30:08
#
#-------------------------------------------------

QT       += widgets opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = openGL_test01
TEMPLATE = app
INSTALLS += target

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui


contains(QT_CONFIG, opengles.) {
    contains(QT_CONFIG, angle): \
        warning("Qt was built with ANGLE, which provides only OpenGL ES 2.0 on top of DirectX 9.0c")
    error("This example requires Qt to be configured with -opengl desktop")
}
