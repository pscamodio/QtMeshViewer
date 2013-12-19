#-------------------------------------------------
#
# Project created by QtCreator 2013-12-19T20:36:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MeshViewer
TEMPLATE = app

linux {
    QMAKE_CXXFLAGS += -std=c++11
}


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
