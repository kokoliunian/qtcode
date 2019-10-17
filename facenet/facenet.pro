#-------------------------------------------------
#
# Project created by QtCreator 2019-10-14T13:53:18
#
#-------------------------------------------------

QT       += core gui
QT += network
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = facenet
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        arcface.cpp \
        base.cpp \
        camthread.cpp \
        clientsession.cpp \
        detectthread.cpp \
        main.cpp \
        mainwindow.cpp \
        mtcnn.cpp \
        sample.cpp \
        sqlitehelper.cpp

HEADERS += \
        arcface.h \
        base.h \
        camthread.h \
        clientsession.h \
        detectthread.h \
        global.h \
        mainwindow.h \
        mtcnn.h \
        sample.h \
        sqlitehelper.h

FORMS += \
        mainwindow.ui \
        sample.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS    += -fopenmp

INCLUDEPATH += C:/opencv/install-qt/install/include\
               C:/opencv/install-qt/install/include\opencv2


LIBS += C:/opencv/install-qt/install/x64/mingw/lib/libopencv_core411.dll.a\
        C:/opencv/install-qt/install/x64/mingw/lib/libopencv_highgui411.dll.a\
        C:/opencv/install-qt/install/x64/mingw/lib/libopencv_calib3d411.dll.a\
        C:/opencv/install-qt/install/x64/mingw/lib/libopencv_dnn411.dll.a\
        C:/opencv/install-qt/install/x64/mingw/lib/libopencv_features2d411.dll.a\
        C:/opencv/install-qt/install/x64/mingw/lib/libopencv_flann411.dll.a\
        C:/opencv/install-qt/install/x64/mingw/lib/libopencv_gapi411.dll.a\
        C:/opencv/install-qt/install/x64/mingw/lib/libopencv_imgcodecs411.dll.a\
        C:/opencv/install-qt/install/x64/mingw/lib/libopencv_imgproc411.dll.a\
        C:/opencv/install-qt/install/x64/mingw/lib/libopencv_ml411.dll.a\
        C:/opencv/install-qt/install/x64/mingw/lib/libopencv_objdetect411.dll.a\
        C:/opencv/install-qt/install/x64/mingw/lib/libopencv_photo411.dll.a\
        C:/opencv/install-qt/install/x64/mingw/lib/libopencv_stitching411.dll.a\
        C:/opencv/install-qt/install/x64/mingw/lib/libopencv_video411.dll.a\
        C:/opencv/install-qt/install/x64/mingw/lib/libopencv_videoio411.dll.a



INCLUDEPATH += F:\code\tmpncnn\ncnn\buildmingw\install\include
LIBS +=F:\code\tmpncnn\ncnn\buildmingw\install\lib\libncnn.a
