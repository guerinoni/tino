include(../tinolibrary.pri)

QT += core gui widgets

INCLUDEPATH += $$PWD/../yaml/yaml-cpp/include

FORMS += \
    $$PWD/MainWindow.ui \

HEADERS += \
    $$PWD/MainWindow.hpp \
    $$PWD/CentralWidget.hpp \
    $$PWD/MainSplitter.hpp \

SOURCES += \
    $$PWD/MainWindow.cpp \
    $$PWD/CentralWidget.cpp \
    $$PWD/MainSplitter.cpp \

