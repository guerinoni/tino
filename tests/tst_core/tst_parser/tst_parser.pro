TINO_LIB_DEPENDS += \
    core \

include(../../tests.pri)

SOURCES += tst_Parser.cpp

INCLUDEPATH += $$PWD/../../helptest/generator/
