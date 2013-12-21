#-------------------------------------------------
#
# Project created by QtCreator 2013-12-19T20:36:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MeshViewer
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    openglwidget.cpp \
    meshviewer.cpp

HEADERS  += mainwindow.h \
    openglwidget.h \
    meshviewer.h

FORMS    += mainwindow.ui

unix:!maxc{
    QMAKE_CXXFLAGS += -std=c++11
    CONFIG(release, debug|release){
        LIBS += -L/usr/local/lib/OpenMesh/ -lOpenMeshCore
    } else {
        LIBS += -L/usr/local/lib/OpenMesh/ -lOpenMeshCored
    }
    INCLUDEPATH += /usr/local/include/OpenMesh
    DEPENDPATH += /usr/local/include/OpenMesh
    PRE_TARGETDEPS += /usr/local/lib/OpenMesh/libOpenMeshCore.a
}
