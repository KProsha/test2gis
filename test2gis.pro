QT += quick

TARGET = test2gis
CONFIG += c++14
DESTDIR = $${PWD}/bin

SOURCES += \
        src/backend/backend.cpp \
        src/backend/parser.cpp \
        src/gui/histogrammodel.cpp \
        src/main.cpp

RESOURCES += resources/qml.qrc

HEADERS += \
    src/backend/backend.h \
    src/backend/histogramstate.h \
    src/backend/parser.h \
    src/gui/histogrammodel.h
