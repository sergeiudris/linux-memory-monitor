TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++14

QMAKE_CXXFLAGS += -std=c++1y -pthread
LIBS += -pthread

SOURCES += \
    main.cpp

HEADERS += \
    dialog.hpp

unix:!macx: LIBS += -L$$OUT_PWD/../iproc/ -liproc

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../

unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../iproc/libiproc.a
