QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += resources_big
CONFIG += static

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
    aboutus.cpp \
    assassin.cpp \
    bullet.cpp \
    choicebutton.cpp \
    gamecontrol.cpp \
    gameview.cpp \
    main.cpp \
    mainwindow.cpp \
    nenecchi.cpp \
    protagonist.cpp \
    pushbutton.cpp \
    settings.cpp \
    spikeweed.cpp \
    sword.cpp \
    welcome.cpp

HEADERS += \
    aboutus.h \
    assassin.h \
    bullet.h \
    choicebutton.h \
    entity.h \
    entity.h \
    gamecontrol.h \
    gameview.h \
    mainwindow.h \
    nenecchi.h \
    protagonist.h \
    pushbutton.h \
    settings.h \
    spikeweed.h \
    sword.h \
    welcome.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QMAKE_LFLAGS += -static-libgcc
QMAKE_LFLAGS += -static-libstdc++
QMAKE_LFLAGS += -static

RESOURCES += \
    resource.qrc
