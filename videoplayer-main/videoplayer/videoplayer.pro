QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
  res.qrc

DISTFILES += \
  images/Progressbar.png \
  images/cd.png \
  images/dd_d.png \
  images/dd_u.png \
  images/heart_d.png \
  images/heart_u.png \
  images/l_d.png \
  images/l_u.png \
  images/music.png \
  images/music_icon.png \
  images/pause_d.png \
  images/pause_u.png \
  images/play_d.png \
  images/play_u.png \
  images/r_d.png \
  images/r_u.png \
  images/s_d.png \
  images/s_u.png \
  images/style.qss \
  images/th-list_d.png \
  images/th-list_u.png \
  images/volume_d.png \
  images/volume_u.png \
  images/屏幕截图 2023-12-31 112846.png \
  video/fireworks.mp4
