QT += quick

TARGET = test2gis
CONFIG += c++14
DESTDIR = $${PWD}/bin

SOURCES += \
        src/main.cpp

RESOURCES += resources/qml.qrc




# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target