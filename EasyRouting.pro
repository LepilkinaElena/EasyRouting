#-------------------------------------------------
#
# Project created by QtCreator 2016-04-12T23:36:37
#
#-------------------------------------------------

QT       += core gui testlib webkit webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EasyRouting
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    Multigraph/cost.cpp \
    ERModel/place.cpp \
    ERModel/routecost.cpp \
    tests/tests.cpp \
    View/mapview.cpp \
    View/selectionitem.cpp \
    View/placedialog.cpp \
    ERModel/citymap.cpp \
    View/routedialog.cpp \
    DAO/IOFileManager.cpp \
    Exceptions/nullpointerexception.cpp \
    Exceptions/absencemultigraphexception.cpp \
    Exceptions/edgeabsencemultigraphexception.cpp \
    Exceptions/vertexabsencemultigraphexception.cpp

HEADERS  += mainwindow.h \
    Multigraph/cost.h \
    Multigraph/edge.h \
    Multigraph/multigraph.h \
    Multigraph/multigraphiterator.h \
    ERModel/place.h \
    ERModel/routecost.h \
    tests/tests.h \
    View/mapview.h \
    View/selectionitem.h \
    Multigraph/multigraphiterator.h \
    View/placedialog.h \
    ERModel/citymap.h \
    View/routedialog.h \
    Multigraph/multigraphallocator.h \
    DAO/DataAccessObject.h \
    DAO/IOFileManager.h \
    ERModel/paramsEntity.hpp \
    ERModel/path.hpp \
    ERModel/routeSearcher.hpp \
    Exceptions/nullpointerexception.h \
    Exceptions/absencemultigraphexception.h \
    Exceptions/edgeabsencemultigraphexception.h \
    Exceptions/vertexabsencemultigraphexception.h

FORMS    += mainwindow.ui \
    View/placedialog.ui \
    View/routedialog.ui

RESOURCES += \
    resources.qrc
