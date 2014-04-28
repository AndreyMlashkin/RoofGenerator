QT       += core

QT       -= gui

TARGET = untitled
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    rule.cpp \
    grammarloader\grammarloader.cpp \
    grammarloader\grammarloaderprivate.cpp \
    grammarloader\grammarnativeloader.cpp \
    grammarloader\grammarjsonloader.cpp \
    wordsgenerator.cpp \
    wordsgeneratorthread.cpp \
    grammarperformer.cpp

HEADERS += \
    generatorapi.h \
    rule.h \
    grammarloader\grammarloader.h \
    grammarloader\grammarloaderprivate.h \
    grammarloader\grammarnativeloader.h \
    grammarloader\grammarjsonloader.h \
    wordsgeneratorthread.h \
    wordsgenerator.h \
    grammarperformer.h \

RESOURCES += \
    ..\list.qrc
