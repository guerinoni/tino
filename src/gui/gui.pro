include(../tinolibrary.pri)

FORMS += \
    $$PWD/MainWindow.ui \
    $$PWD/DialogAbout.ui \
    $$PWD/DialogSerialSettings.ui

HEADERS += \
    $$PWD/MainWindow.hpp \
    $$PWD/DialogAbout.hpp \
    $$PWD/ConfigViewFactory.hpp \
    $$PWD/DialogSerialSettings.hpp \
    $$PWD/MdiChild.hpp \
    $$PWD/Led.hpp \
    $$PWD/ByteWidget.hpp \
    $$PWD/WordWidget.hpp

SOURCES += \
    $$PWD/MainWindow.cpp \
    $$PWD/DialogAbout.cpp \
    $$PWD/ConfigViewFactory.cpp \
    $$PWD/DialogSerialSettings.cpp \
    $$PWD/MdiChild.cpp \
    $$PWD/Led.cpp \
    $$PWD/ByteWidget.cpp \
    $$PWD/WordWidget.cpp

RESOURCES += \
    $$PWD/gui_resources.qrc
