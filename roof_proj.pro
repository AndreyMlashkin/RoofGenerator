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
    grammarperformer\rule.cpp \
    basepainter.cpp \
    elementaryblock.cpp \
    flowpainter.cpp \
    roof.cpp \
    grammarperformer\grammarloader\grammarloader.cpp \
    grammarperformer\grammarloader\grammarloaderprivate.cpp \
    grammarperformer\grammarloader\grammarnativeloader.cpp \
    grammarperformer\grammarloader\grammarjsonloader.cpp \
    grammarperformer\wordsgenerator.cpp \
    grammarperformer\grammarperformer.cpp

HEADERS += \
    grammarperformer\generatorapi.h \
    rule.h \
    basepainter.h \
    elementaryblock.h \
    flowpainter.h \
    roof.h \
    grammarperformer\grammarloader\grammarloader.h \
    grammarperformer\grammarloader\grammarloaderprivate.h \
    grammarperformer\grammarloader\grammarnativeloader.h \
    grammarperformer\grammarloader\grammarjsonloader.h \
    grammarperformer\wordsgenerator.h \
    grammarperformer\grammarperformer.h

RESOURCES += \
    list.qrc

FORMS += \
    roof.ui
