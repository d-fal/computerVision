#-------------------------------------------------
#
# Project created by QtCreator 2014-10-09T13:06:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = openCV_Test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH += C:\OpenCV\opencv_bin\install\include

LIBS += -LC:\\OpenCV\\opencv_bin\\install\\x64\\mingw\\lib \
    libopencv_core249 \
    libopencv_highgui249 \
    libopencv_imgproc249 \
    libopencv_features2d249 \
    libopencv_calib3d249
