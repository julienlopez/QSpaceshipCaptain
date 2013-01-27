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
    $$QSPACESHIPCAPTAIN_SRC/utils/stringlist.cpp


HEADERS += \
    teststringlist.hpp \
    $$QSPACESHIPCAPTAIN_SRC/utils/stringlist.hpp
