#-------------------------------------------------
#
# Project created by QtCreator 2014-10-12T15:59:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = opencvTest03
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    colordetect.cpp \
    histogram1d.cpp \
    watershedsegmenter.cpp \
    preprocessing.cpp \
    characterrecognition.cpp \
    humomments.cpp \
    readcharacterdata.cpp

HEADERS  += mainwindow.h \
    colordetect.h \
    histogram1d.h \
    watershedsegmenter.h \
    preprocessing.h \
    characterrecognition.h \
    humomments.h \
    readcharacterdata.h

FORMS    += mainwindow.ui

INCLUDEPATH += C:\OpenCV\myBuild\install\include

LIBS += -LC:\\OpenCV\\myBuild\\install\\x64\\mingw\\lib \
    libopencv_core249d \
    libopencv_highgui249d \
    libopencv_imgproc249d \
    libopencv_features2d249d \
    libopencv_calib3d249d \
    libopencv_flann249d \
    libopencv_gpu249d \
    libopencv_nonfree249d \
    libopencv_objdetect249d \
    libopencv_ocl249d \
    libopencv_photo249d \
    libopencv_stitching249d \
    libopencv_superres249d \
    libopencv_video249d \
    libopencv_videostab249d\
    libopencv_ml249d
