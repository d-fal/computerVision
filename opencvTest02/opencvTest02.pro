#-------------------------------------------------
#
# Project created by QtCreator 2014-10-09T20:46:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = opencvTest02
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        assets.cpp \
    colordetector.cpp

HEADERS  += mainwindow.h \
    assets.h \
    colordetector.h

FORMS    += mainwindow.ui


INCLUDEPATH += C:\OpenCV\opencv_bin\install\include

LIBS += -LC:\\OpenCV\\opencv_bin\\install\\x64\\mingw\\lib \
    libopencv_core249 \
    libopencv_highgui249 \
    libopencv_imgproc249 \
    libopencv_features2d249 \
    libopencv_calib3d249 \
    libopencv_flann249 \
    libopencv_gpu249 \
    libopencv_nonfree249 \
    libopencv_objdetect249 \
    libopencv_ocl249 \
    libopencv_photo249 \
    libopencv_stitching249 \
    libopencv_superres249 \
    libopencv_video249 \
    libopencv_videostab249
