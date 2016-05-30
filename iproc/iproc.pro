#-------------------------------------------------
#
# Project created by QtCreator 2016-05-18T22:25:38
#
#-------------------------------------------------

QT       -= core gui

TARGET = iproc
TEMPLATE = lib
CONFIG += staticlib

SOURCES +=

HEADERS += \
    concurrent.hpp \
    group.hpp \
    io.hpp \
    meminfo.hpp \
    message.hpp \
    page.hpp \
    pageset.hpp \
    process.hpp \
    procinterface.hpp \
    text.hpp \
    arithm.hpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}

#QMAKE_CXXFLAGS += -std=c++11
#CONFIG += c++11
#QMAKE_CXXFLAGS += -std=c++1y
CONFIG += c++14
