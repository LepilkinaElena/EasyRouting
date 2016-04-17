#-------------------------------------------------
#
# Project created by QtCreator 2016-04-12T23:36:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EasyRouting
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Multigraph/cost.cpp \
    ERModel/place.cpp \
    ERModel/routecost.cpp

HEADERS  += mainwindow.h \
    Multigraph/cost.h \
    Multigraph/edge.h \
    Multigraph/multigraph.h \
    ERModel/place.h \
    ERModel/routecost.h

FORMS    += mainwindow.ui
