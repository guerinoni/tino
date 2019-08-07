TINO_LIB_DEPENDS += \
    core

include(../../tests.pri) #not sure

HEADERS += $$PWD\Generator.hpp
SOURCES += $$PWD\Generator.cpp

INCLUDEPATH += ../../../src/core/
