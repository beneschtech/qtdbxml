#-------------------------------------------------
#
# Project created by QtCreator 2018-11-20T22:04:48
#
#-------------------------------------------------

QT       += sql xml

QT       -= gui

TARGET = qtdbxml
TEMPLATE = lib
CONFIG += staticlib c++11

SOURCES += \
        qtdbxml.cpp

HEADERS += \
        qtdbxml.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
