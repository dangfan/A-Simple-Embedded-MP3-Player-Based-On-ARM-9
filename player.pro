#-------------------------------------------------
#
# Project created by QtCreator 2011-05-17T20:42:00
#
#-------------------------------------------------

QT       += core gui

TARGET = player
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    musiclibrary.cpp \
    song.cpp \
    controller.cpp \
    listviewdelegate.cpp

HEADERS  += mainwindow.h \
    musiclibrary.h \
    song.h \
    status.h \
    controller.h \
    listviewdelegate.h

FORMS    += mainwindow.ui

LIBS     += -L/usr/local/lib -ltag

INCLUDEPATH += /usr/local/taglib/include

RESOURCES += \
    resources.qrc
