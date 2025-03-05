#-------------------------------------------------
#
# Project created by QtCreator 2020-01-16T19:07:01
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++17

TARGET = PlaneWar
TEMPLATE = app


SOURCES += main.cpp\
        mainscene.cpp \
    map.cpp \
    heroplane.cpp \
    bullet.cpp \
    enemyplane.cpp \
    bomb.cpp

HEADERS  += mainscene.h \
    config.h \
    map.h \
    heroplane.h \
    bullet.h \
    enemyplane.h \
    bomb.h

RESOURCES += \
    res.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
QMAKE_PROJECT_DEPTH = 0
QMAKE_CXXFLAGS += /utf-8
