#-------------------------------------------------
#
# Project created by QtCreator 2017-08-15T21:15:56
#
#-------------------------------------------------

QT       += core gui
QT +=widgets multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tank_3000
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    base.cpp \
    enemytank.cpp \
    mytank.cpp \
    home.cpp \
    bullet.cpp \
    linklist.cpp \
    map.cpp \
    dynamic.cpp \
    tank.cpp \
    collision.cpp \
    gametool.cpp \
    rsa.cpp \
    bplustree.cpp \
    denglu.cpp \
    inputdlg.cpp

HEADERS  += mainwindow.h \
    base.h \
    data.h \
    enemytank.h \
    mytank.h \
    home.h \
    bullet.h \
    linklist.h \
    map.h \
    dynamic.h \
    tank.h \
    collision.h \
    gametool.h \
    rsa.h \
    bplustree.h \
    denglu.h \
    inputdlg.h

RESOURCES += \
    src.qrc
