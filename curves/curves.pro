#-------------------------------------------------
#
# Project created by QtCreator 2019-09-27T09:18:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = curves
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    curvedata.cpp \
    curvescene.cpp

HEADERS  += widget.h \
    curvedata.h \
    curvescene.h

FORMS    += widget.ui
