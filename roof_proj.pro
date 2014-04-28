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
    grammarperformer\grammarloader\grammarloader.cpp \
    grammarperformer\grammarloader\grammarloaderprivate.cpp \
    grammarperformer\grammarloader\grammarnativeloader.cpp \
    grammarperformer\grammarloader\grammarjsonloader.cpp \
    grammarperformer\wordsgenerator.cpp \
    grammarperformer\grammarperformer.cpp \
    mainwindow.cpp \
    roofui/roofimage.cpp \
    roofui/roofimagesmodel.cpp \
    roofui/roofimagedelegate.cpp \
    roofui/listtotableproxy.cpp
    grammarperformer/wordsgeneratorthread.cpp

HEADERS += \
    grammarperformer\generatorapi.h \
    grammarperformer\rule.h \
    basepainter.h \
    elementaryblock.h \
    flowpainter.h \
    grammarperformer\grammarloader\grammarloader.h \
    grammarperformer\grammarloader\grammarloaderprivate.h \
    grammarperformer\grammarloader\grammarnativeloader.h \
    grammarperformer\grammarloader\grammarjsonloader.h \
    grammarperformer\wordsgenerator.h \
    grammarperformer\grammarperformer.h \
    mainwindow.h \
    roofui/roofimage.h \
    roofui/roofimagesmodel.h \
    roofui/roofimagedelegate.h \
    listtotableproxy.h \
    roofui/listtotableproxy.h
    grammarperformer/wordsgeneratorthread.h

RESOURCES += \
    list.qrc

FORMS += \
    roof.ui \
    askDialog.ui
