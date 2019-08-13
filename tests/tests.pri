include($$PWD/../tino.pri)

isEmpty(TEMPLATE):TEMPLATE = app
QT += testlib core gui widgets
CONFIG += qt warn_on console depend_includepath testcase
CONFIG -= app_bundle

INCLUDEPATH += $$PWD/helptest/generator/
