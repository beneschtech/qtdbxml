#-------------------------------------------------
#
# Project created by QtCreator 2018-11-22T21:19:51
#
#-------------------------------------------------

QT       += sql xml testlib

QT       -= gui

TARGET = tst_connecttest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
        tst_connecttest.cpp

INCLUDEPATH = ../../lib/qtdbxml
LIBS += ../../lib/qtdbxml/libqtdbxml.a
TARGETDEPS += ../../lib/qtdbxml/libqtdbxml.a
