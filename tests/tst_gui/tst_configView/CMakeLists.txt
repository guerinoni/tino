set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Gui Test Widgets SerialPort SerialBus Svg Widgets REQUIRED)

add_executable(tst_configView
    ../../../src/core/Bitset.cpp     ../../../src/core/Bitset.hpp
    ../../../src/core/Block.cpp      ../../../src/core/Block.hpp
    ../../../src/core/Byte.cpp       ../../../src/core/Byte.hpp
    ../../../src/core/Element.cpp    ../../../src/core/Element.hpp
    ../../../src/core/Protocol.cpp   ../../../src/core/Protocol.hpp
    ../../../src/core/Settings.cpp   ../../../src/core/Settings.hpp
    ../../../src/core/Word.cpp       ../../../src/core/Word.hpp

    ../../../src/parser/ConfigParser.cpp   ../../../src/parser/ConfigParser.hpp


    ../../../src/serialcom/ModbusCom.cpp   ../../../src/serialcom/ModbusCom.hpp

    ../../../src/gui/ConfigViewFactory.cpp       ../../../src/gui/ConfigViewFactory.hpp
    ../../../src/gui/Led.cpp                     ../../../src/gui/Led.hpp
    ../../../src/gui/MdiChild.cpp                ../../../src/gui/MdiChild.hpp
    ../../../src/gui/ValueWidget.cpp             ../../../src/gui/ValueWidget.hpp
    ../../../src/gui/DialogAbout.cpp             ../../../src/gui/DialogAbout.hpp             ../../../src/gui/DialogAbout.ui
    ../../../src/gui/DialogSerialSettings.cpp    ../../../src/gui/DialogSerialSettings.hpp    ../../../src/gui/DialogSerialSettings.ui
    ../../../src/gui/MainWindow.cpp              ../../../src/gui/MainWindow.hpp              ../../../src/gui/MainWindow.ui

    tst_ConfigView.cpp)

target_link_libraries(tst_configView PRIVATE Qt5::Core Qt5::Gui Qt5::Test Qt5::Widgets Qt5::SerialPort Qt5::SerialBus Qt5::Svg)
