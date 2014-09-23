#-------------------------------------------------
#
# Project created by QtCreator 2014-09-10T20:28:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Spreadsheet
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    finddialog.cpp \
    gotocell.cpp \
    sortdialong.cpp \
    spreadsheet.cpp \
    cell.cpp

HEADERS  += mainwindow.h \
    finddialog.h \
    gotocell.h \
    sortdialong.h \
    spreadsheet.h \
    cell.h

RESOURCES += \
    Icons.qrc

FORMS += \
    gotocell.ui \
    sortdialong.ui
