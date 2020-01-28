!isEmpty(TINO_PRI_INCLUDED):error("tino.pri already included")
TINO_PRI_INCLUDED = 1

TINO_LIB_DIRS = $$PWD/src/
TINO_BUILD_DIR = $$shadowed($$PWD)

DEFINES *= TINO_PROJECT_DIR=$$absolute_path($$FILE)

CONFIG += c++17

CONFIG(debug, debug|release) {
    QMAKE_CXXFLAGS += --coverage
    QMAKE_LFLAGS += --coverage
}

defineTest(minQtVersion) {
    maj = $$1
    min = $$2
    patch = $$3
    isEqual(QT_MAJOR_VERSION, $$maj) {
        isEqual(QT_MINOR_VERSION, $$min) {
            isEqual(QT_PATCH_VERSION, $$patch) {
                return(true)
            }
            greaterThan(QT_PATCH_VERSION, $$patch) {
                return(true)
            }
        }
        greaterThan(QT_MINOR_VERSION, $$min) {
            return(true)
        }
    }
    greaterThan(QT_MAJOR_VERSION, $$maj) {
        return(true)
    }
    return(false)
}

defineReplace(qtLibraryTargetName) {
    unset(LIBRARY_NAME)
    LIBRARY_NAME = $$1
    CONFIG(debug, debug|release) {
        mac:RET = $$member(LIBRARY_NAME, 0)_debug
        else:win32:RET = $$member(LIBRARY_NAME, 0)d
    }

    isEmpty(RET):RET = $$LIBRARY_NAME
    return($$RET)
}

defineReplace(qtLibraryName) {
   RET = $$qtLibraryTargetName($$1)
   win32 {
      VERSION_LIST = $$split(TINO_VERSION, .)
      RET = $$RET$$first(VERSION_LIST)
   }

   return($$RET)
}

# recursively resolve library deps
done_libs =
for(ever) {
    isEmpty(TINO_LIB_DEPENDS): \
        break()
    done_libs += $$TINO_LIB_DEPENDS
    for(dep, TINO_LIB_DEPENDS) {
        dependencies_file =
        for(dir, TINO_LIB_DIRS) {
            exists($$dir/$$dep/$${dep}_dependencies.pri) {
                dependencies_file = $$dir/$$dep/$${dep}_dependencies.pri
                break()
            }
        }

        isEmpty(dependencies_file): \
            error("Library dependency $$dep not found")
        include($$dependencies_file)
        LIBS *= -L$$TINO_BUILD_DIR/src/$$dep -l$$qtLibraryName($$TINO_LIB_NAME)
        PRE_TARGETDEPS += $$TINO_BUILD_DIR/src/$$dep/$${QMAKE_PREFIX_STATICLIB}$$qtLibraryName($$TINO_LIB_NAME).$${QMAKE_EXTENSION_STATICLIB}
        INCLUDEPATH *= $$TINO_LIB_DIRS$$dep
        DEPENDPATH *= $$TINO_LIB_DIRS$$dep
    }
    TINO_LIB_DEPENDS = $$unique(TINO_LIB_DEPENDS)
    TINO_LIB_DEPENDS -= $$unique(done_libs)
}
