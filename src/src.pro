include(../QSpaceshipCaptain.pri)

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QSpaceshipCaptain
TEMPLATE = app

OBJECTS_DIR = $$QSPACESHIPCAPTAIN_OBJ
MOC_DIR = $$QSPACESHIPCAPTAIN_MOC

INCLUDEPATH += .

SOURCES += main.cpp\
        mainwindow.cpp \
    ship/ship.cpp \
    ship/room.cpp \
    utils/json.cpp \
    utils/any/any.cpp \
    ship/system.cpp \
    shipdisplay.cpp \
    utils/stringlist.cpp \
    utils/point.cpp \
    pathinghelper.cpp \
    ship/door.cpp \
    ship/crewmember.cpp \
    crewwidget.cpp \
    crewmemberwidget.cpp \
    ship/graph/graphhelper.cpp \
    ship/graph/shipgraph.cpp

HEADERS  += mainwindow.hpp \
    ship/ship.hpp \
    ship/room.hpp \
    utils/types.hpp \
    utils/singleton.hpp \
    utils/factory.hpp \
    utils/defaultfactoryerrorpolicy.hpp \
    utils/traits/parametertrait.hpp \
    utils/size.hpp \
    utils/json.hpp \
    utils/any/any.hpp \
    ship/system.hpp \
    shipdisplay.hpp \
    utils/stringlist.hpp \
    utils/point.hpp \
    pathinghelper.hpp \
    ship/door.hpp \
    ship/crewmember.hpp \
    utils/typetrait.hpp \
    utils/select.hpp \
    utils/ispointer.hpp \
    utils/comparator.hpp \
    utils/comparatormethodvalue.hpp \
    crewwidget.hpp \
    crewmemberwidget.hpp \
    utils/typedefs.hpp \
    utils/iupdateable.hpp \
    ship/graph/graphhelper.hpp \
    ship/graph/shipgraph.hpp

