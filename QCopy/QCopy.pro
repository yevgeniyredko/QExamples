QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QCopy
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
        mainwindow.cpp \
    copier.cpp

HEADERS  += mainwindow.h \
    copier.h

FORMS    += mainwindow.ui
