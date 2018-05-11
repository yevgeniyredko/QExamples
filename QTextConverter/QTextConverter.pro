QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTextConverter
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
        mainwindow.cpp \
    textconverter.cpp

HEADERS  += mainwindow.h \
    textconverter.h

FORMS    += mainwindow.ui
