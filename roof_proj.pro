#-------------------------------------------------
#
# Project created by QtCreator 2014-03-12T23:11:19
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = roof_proj
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    grammargenerator.cpp \
    rule.cpp \
    basepainter.cpp \
    elementaryblock.cpp \
    flowpainter.cpp \
    roof.cpp \
    grammarloader\grammarloader.cpp \
    grammarloader\grammarloaderprivate.cpp \
    grammarloader\grammarnativeloader.cpp \
    grammarloader\grammarjsonloader.cpp \
    wordsgenerator.cpp

HEADERS += \
    generatorapi.h \
    grammargenerator.h \
    rule.h \
    basepainter.h \
    elementaryblock.h \
    flowpainter.h \
    roof.h \
    grammarloader\grammarloader.h \
    grammarloader\grammarloaderprivate.h \
    grammarloader\grammarnativeloader.h \
    grammarloader\grammarjsonloader.h \
    wordsgenerator.h

RESOURCES += \
    list.qrc

FORMS += \
    roof.ui
