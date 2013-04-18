#-------------------------------------------------
#
# Project created by QtCreator 2013-04-13T19:48:02
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QMine
TEMPLATE = app

!win32 {
    QMAKE_CXXFLAGS  += -W -Wall -std=c++11
}

SOURCES += main.cpp\
        Window.cpp \
    ConnectionDialog.cpp \
    requests/AuthenticateRequest.cpp \
    requests/IRequest.cpp

HEADERS  += Window.hpp \
    ConnectionDialog.hpp \
    requests/AuthenticateRequest.hpp \
    requests/IRequest.hpp

FORMS    += Window.ui \
    ConnectionDialog.ui
