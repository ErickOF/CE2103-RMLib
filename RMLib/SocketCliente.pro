#-------------------------------------------------
#
# Project created by QtCreator 2017-08-12T10:53:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SocketCliente
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    socketcliente.cpp

HEADERS  += mainwindow.h \
    socketcliente.h \
    json.hpp

FORMS    += mainwindow.ui
