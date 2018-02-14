#-------------------------------------------------
#
# Project created by QtCreator 2016-05-16T09:06:48
#
#-------------------------------------------------

QT       += core gui
QT       += network
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FireControlSystem
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    udppeer.cpp \
    message.cpp \
    degreeconverter.cpp

HEADERS  += mainwindow.h \
    message.h \
    udppeer.h \
    degreeconverter.h

FORMS    += mainwindow.ui
