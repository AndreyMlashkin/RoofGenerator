#-------------------------------------------------
#
# Project created by QtCreator 2014-02-14T16:05:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = grammar
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    grammar.cpp \
    elementaryblock.cpp \
    basepainter.cpp \
    flowpainter.cpp \
    roof.cpp

HEADERS  += mainwindow.h \
    grammar.h \
    elementaryblock.h \
    basepainter.h \
    flowpainter.h \
    roof.h

FORMS    += mainwindow.ui \
    roof.ui

RESOURCES += \
    list.qrc

OTHER_FILES +=
