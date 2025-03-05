#-------------------------------------------------
#
# Project created by QtCreator 2018-12-19T19:59:54
#
#-------------------------------------------------

QT       += core gui
QT += multimedia
QT += multimediawidgets

RC_ICONS = bitbug_favicon.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mediaplay
TEMPLATE = app


SOURCES += main.cpp\
        mediaplay.cpp

HEADERS  += mediaplay.h

FORMS    += mediaplay.ui

RESOURCES += \
    image.qrc
