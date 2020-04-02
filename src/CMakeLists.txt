set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets SerialPort SerialBus Svg REQUIRED)

add_executable(${CMAKE_PROJECT_NAME}
    core/Bitset.cpp     core/Bitset.hpp
    core/Block.cpp      core/Block.hpp
    core/Byte.cpp       core/Byte.hpp
    core/Element.cpp    core/Element.hpp
    core/Protocol.cpp   core/Protocol.hpp
    core/Settings.cpp   core/Settings.hpp
    core/Word.cpp       core/Word.hpp

    parser/ConfigParser.cpp parser/ConfigParser.hpp

    serialcom/ModbusCom.cpp serialcom/ModbusCom.hpp

    gui/ConfigViewFactory.cpp       gui/ConfigViewFactory.hpp
    gui/Led.cpp                     gui/Led.hpp
    gui/MdiChild.cpp                gui/MdiChild.hpp
    gui/ValueWidget.cpp             gui/ValueWidget.hpp
    gui/DialogAbout.cpp             gui/DialogAbout.hpp             gui/DialogAbout.ui
    gui/DialogSerialSettings.cpp    gui/DialogSerialSettings.hpp    gui/DialogSerialSettings.ui
    gui/MainWindow.cpp              gui/MainWindow.hpp              gui/MainWindow.ui

    gui/icons/icons.qrc

    app/main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets
                                                    Qt5::SerialPort Qt5::SerialBus Qt5::Svg)

add_definitions(-DVERSION=\"${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}\")
