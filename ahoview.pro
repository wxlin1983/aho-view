#-------------------------------------------------
#
# Project created by QtCreator 2014-06-15T14:47:27
#
#-------------------------------------------------

QT       += core gui

INCLUDEPATH += "C:/Users/Wei-Hsun Lin/My Library/zlib-1.2.8"

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ahoview
TEMPLATE = app


SOURCES += main.cpp\
        ahoview.cpp \
    pic.cpp \
    picaxiv.cpp

HEADERS  += ahoview.h \
    pic.h \
    picaxiv.h

FORMS    += ahoview.ui
