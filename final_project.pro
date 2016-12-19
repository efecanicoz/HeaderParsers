#-------------------------------------------------
#
# Project created by QtCreator 2016-12-18T22:29:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = final_project
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    arrayReader.cpp \
    block.cpp \
    elf32.cpp \
    elf64.cpp \
    exe32.cpp \
    exe64.cpp \
    fileReader.cpp \
    instruction.cpp \
    reader.cpp

HEADERS  += mainwindow.h \
    arrayReader.h \
    block.h \
    EInterface.h \
    elf32.h \
    elf64.h \
    exe32.h \
    exe64.h \
    fileReader.h \
    instruction.h \
    opcode.h \
    reader.h

FORMS    += mainwindow.ui

DISTFILES += \
    final_project.pro.user
