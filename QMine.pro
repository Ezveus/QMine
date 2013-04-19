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

win32 {
    DEFINES += WINDOWS_SYSTEM
}

debug {
    DEFINES += DEBUG_VERSION
}

SOURCES += main.cpp\
        Window.cpp \
    ConnectionDialog.cpp \
    requests/AuthenticateRequest.cpp \
    requests/ARequest.cpp \
    requests/LoadRequest.cpp \
    requests/FileUploader.cpp

HEADERS  += Window.hpp \
    ConnectionDialog.hpp \
    requests/AuthenticateRequest.hpp \
    requests/ARequest.hpp \
    requests/LoadRequest.hpp \
    requests/FileUploader.hpp

FORMS    += Window.ui \
    ConnectionDialog.ui
