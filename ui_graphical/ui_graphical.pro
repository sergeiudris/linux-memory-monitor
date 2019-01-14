#-------------------------------------------------
#
# Project created by QtCreator 2015-05-18T11:15:20
#
#-------------------------------------------------

QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ui_graphical
TEMPLATE = app



FORMS    += mainwindow.ui


#QMAKE_CXXFLAGS += -std=c++1y
#QMAKE_CXXFLAGS += -std=c++11
#CONFIG += c++11
CONFIG += c++14




HEADERS += \
    bg.h \
    mainwindow.h \
    scene.h

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    scene.cpp

unix:!macx: LIBS += -L$$OUT_PWD/../iproc/ -liproc

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../

unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../iproc/libiproc.a
