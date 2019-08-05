include(app_dependencies.pri)
include(../../tino.pri)

TEMPLATE = app
CONFIG += qtc_runnable sliced_bundle
TARGET = tino
QT -= testlib
QT += core gui widgets

INCLUDEPATH += $$PWD/../gui

CONFIG(release, debug|release) {
    QMAKE_CXXFLAGS += -O3
}

CONFIG(debug, debug|release) {
    QMAKE_CXXFLAGS += -O0
    QMAKE_CXXFLAGS -= -O1
    QMAKE_CXXFLAGS -= -O2
    QMAKE_CXXFLAGS -= -O3
    QMAKE_CXXFLAGS += --debug
}

SOURCES += \
    $$PWD/main.cpp \


