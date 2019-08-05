depfile = $$replace(_PRO_FILE_PWD_, ([^/]+$), \\1/\\1_dependencies.pri)
exists($$depfile) {
    include($$depfile)
    isEmpty(TINO_LIB_NAME): \
        error("$$basename(depfile) does not define TINO_LIB_NAME.")
} else {
    isEmpty(TINO_LIB_NAME): \
        error("TINO_LIB_NAME is empty. Maybe you meant to create $$basename(depfile)?")
}

TARGET = $$TINO_LIB_NAME
CONFIG -= debug_and_release debug_and_release_target

CONFIG(release, debug|release) {
    QMAKE_CXXFLAGS += -O3
}

CONFIG(debug, debug|release) {
    QMAKE_CXXFLAGS += -O0
    QMAKE_CXXFLAGS -= -O1
    QMAKE_CXXFLAGS -= -O2
    QMAKE_CXXFLAGS -= -O3
    QMAKE_CXXFLAGS += --debug
    QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
    LIBS += -lgcov
}


include(../tino.pri)

TEMPLATE = lib
CONFIG += shared dll

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

TARGET = $$qtLibraryTargetName($$TARGET)
