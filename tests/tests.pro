include(../QSpaceshipCaptain.pri)

QT += testlib
QT -= gui

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

OBJECTS_DIR = $$QSPACESHIPCAPTAIN_OBJ_TESTS
MOC_DIR = $$QSPACESHIPCAPTAIN_MOC_TESTS

INCLUDEPATH += $$QSPACESHIPCAPTAIN_SRC

SOURCES += main.cpp \
    teststringlist.cpp \
    $$QSPACESHIPCAPTAIN_SRC/utils/stringlist.cpp \
    $$QSPACESHIPCAPTAIN_SRC/utils/any/any.cpp \
    $$QSPACESHIPCAPTAIN_SRC/utils/json.cpp \
    $$QSPACESHIPCAPTAIN_SRC/utils/point.cpp \
    $$QSPACESHIPCAPTAIN_SRC/ship/room.cpp \
    $$QSPACESHIPCAPTAIN_SRC/ship/system.cpp \
    testroom.cpp \
    testjson.cpp


HEADERS += \
    teststringlist.hpp \
    $$QSPACESHIPCAPTAIN_SRC/utils/stringlist.hpp \
    $$QSPACESHIPCAPTAIN_SRC/utils/any/any.hpp \
    $$QSPACESHIPCAPTAIN_SRC/utils/json.hpp \
    $$QSPACESHIPCAPTAIN_SRC/utils/point.hpp \
    $$QSPACESHIPCAPTAIN_SRC/ship/room.hpp \
    $$QSPACESHIPCAPTAIN_SRC/ship/system.hpp \
    testroom.hpp \
    testjson.hpp
