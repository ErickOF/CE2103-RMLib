QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sockets
QMAKE_CXXFLAGS += -std=c++0x -lpthread
LIBS += -lpthread
TEMPLATE = app

SOURCES += main.cpp \
    socketserver.cpp \
    mainwindow.cpp \
    memory.cpp \
    cache.cpp \
    nodememory.cpp \
    nodecache.cpp

HEADERS += \
    socketserver.h \
    mainwindow.h \
    memory.h \
    cache.h \
    nodememory.h \
    nodecache.h

FORMS += \
    mainwindow.ui

