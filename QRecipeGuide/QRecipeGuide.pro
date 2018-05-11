
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QRecipeGuide
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
        mainwindow.cpp \
    recipeedit/recipeedit.cpp \
    ingredientedit/ingredientedit.cpp

HEADERS  += mainwindow.h \
    recipeedit/recipeedit.h \
    ingredientedit/ingredientedit.h

FORMS    += mainwindow.ui \
    recipeedit/recipeedit.ui \
    ingredientedit/ingredientedit.ui

DISTFILES += \
    db.sqlite
