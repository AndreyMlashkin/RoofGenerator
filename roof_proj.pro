#-------------------------------------------------
#
# Project created by QtCreator 2014-03-12T23:11:19
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = roof_proj
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    grammargenerator.cpp \
    rule.cpp \
    grammarnativeloader.cpp

HEADERS += \
    grammargenerator.h \
    rule.h \
    generatorapi.h \
    grammarnativeloader.h \
    grammarloader.h
