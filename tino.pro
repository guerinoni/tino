include(tino.pri)

!minQtVersion(5, 12, 4) {
    message("Cannot build $$IDE_DISPLAY_NAME with Qt version $${QT_VERSION}.")
    error("Use at least Qt 5.12.4.")
}

TEMPLATE  = subdirs
CONFIG   += ordered
SUBDIRS = src tests
